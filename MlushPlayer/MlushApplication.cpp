#include "MlushApplication.h"

#include <QFileInfo>

#include "PlaylistController.h"

MlushApplication::MlushApplication(int &argc, char **argv) :
	QApplication(argc, argv)
{
	setApplicationName("MlushPlayer");
	setApplicationVersion("0.01a");
}

void MlushApplication::Initialize()
{
	m_vkManager = new VkManager(this);

	QString cookies;
	QByteArray binaryCookies;
	QFile file("userdata");
	if ( file.open(QIODevice::ReadOnly) )
	{
		QDataStream stream( &file );
		stream >> binaryCookies;
		cookies = QByteArray::fromBase64(binaryCookies);
	}

	mainWindow()->GetAuthPage()->setCookies(cookies);
	mainWindow()->GetAuthPage()->SetAppID(CONST_APP_ID);
	mainWindow()->GetAuthPage()->SetPermissions(VkOAuthView::Audio);

	connect(mainWindow()->GetAuthPage(), &VkOAuthView::AuthSuccess, [this](const QString &accessToken, int expiresInSecs, int userID)
	{
		QByteArray binaryCookies = mainWindow()->GetAuthPage()->getCookies().toLatin1();
		QFile file("userdata");
		if ( file.open(QIODevice::WriteOnly | QIODevice::Truncate) )
		{
			QDataStream stream( &file );
			stream << binaryCookies.toBase64();
		}

		m_vkManager->SetUserData(accessToken, expiresInSecs, userID);
		m_vkManager->GetPlaylist();
	});

	connect(m_vkManager, &VkManager::success, [this](const QString &playlist)
	{
		mainWindow()->SetPage(MainWindow::PagePlayer);
		mainWindow()->GetPlayerPage()->AddToPlaylist(GetPlaylistFromJSON(playlist), true);
	});

	//@todo Делать это по кнопке
	mainWindow()->GetAuthPage()->OpenAuthPage();
}
