#include <QObject>
#include <QString>

#define ADD_PROPERTY(propName) \
Q_PROPERTY(QString propName READ propName CONSTANT)\
public: static QString propName() {return #propName;}

class MlushConnectorID : public QObject
{
	Q_OBJECT

	ADD_PROPERTY(PLAYLIST_RECIEVED)
	ADD_PROPERTY(PLAYLIST_REQUEST)
	ADD_PROPERTY(SEARCH_REQUEST)

public:
	explicit MlushConnectorID(QObject *parent = 0) : QObject(parent) {}
};
