#include "ObjectsConnector.h"

/// Идентификатор для сигналов
static const std::string TYPE_SIGNAL = "TYPE_SIGNAL";
/// Идентификатор для слотов
static const std::string TYPE_SLOT = "TYPE_SLOT";

ObjectsConnector::MetaObjectsMap ObjectsConnector::m_metaCollector = ObjectsConnector::MetaObjectsMap();

//.............................................................................

ObjectsConnector::ObjectsConnector(QObject *parent/* = 0*/) :
	QObject(parent)
{

}

//.............................................................................

void ObjectsConnector::registerEmitter(const QString &ID, QObject *sender, const QString &signal, bool queued/* = false*/)
{
	const std::string signal_str = signal.startsWith('2') ? signal.toStdString() : QString("2%1").arg(signal).toStdString();

	// Устанавливаем соединение со всеми сигналами для данного типа.
	Q_FOREACH(const auto record, m_metaCollector[ID][TYPE_SLOT])
	{
		if (sender != record.first)
			connect(sender, signal_str.c_str(), record.first, record.second.c_str(), queued ? Qt::QueuedConnection : Qt::UniqueConnection);
	}

	registerMetaType(ID, TYPE_SIGNAL, std::make_pair(sender, signal_str));
}

//.............................................................................

void ObjectsConnector::registerReceiver(const QString &ID, QObject *receiver, const QString &slot, bool queued/* = false*/)
{
	const std::string slot_str = slot.startsWith('1') ? slot.toStdString() : QString("1%1").arg(slot).toStdString();

	// Устанавливаем соединение со всеми слотами для данного типа.
	Q_FOREACH(const auto record, m_metaCollector[ID][TYPE_SIGNAL])
	{
		if (receiver != record.first)
			connect(record.first, record.second.c_str(), receiver, slot_str.c_str(), queued ? Qt::QueuedConnection : Qt::UniqueConnection);
	}

	registerMetaType(ID, TYPE_SLOT, std::make_pair(receiver, slot_str));
}

//.............................................................................

void ObjectsConnector::unregisterReceiver(const QString &ID, QObject *receiver, const QString &slot)
{
	const std::string slot_str = slot.startsWith('1') ? slot.toStdString() : QString("1%1").arg(slot).toStdString();

	// Ликвидируем соединение со всеми сигналами для данного типа.
	Q_FOREACH(const auto record, m_metaCollector[ID][TYPE_SIGNAL])
	{
		if (receiver != record.first)
			disconnect(record.first, record.second.c_str(), receiver, slot_str.c_str());
	}

	m_metaCollector[ID][TYPE_SLOT].remove(std::make_pair(receiver, slot_str));
}

//.............................................................................

void ObjectsConnector::unregisterEmitter(const QString &ID, QObject *sender, const QString &signal)
{
	const std::string signal_str = signal.startsWith('2') ? signal.toStdString() : QString("2%1").arg(signal).toStdString();

	// Ликвидируем соединение со всеми сигналами для данного типа.
	Q_FOREACH(const auto record, m_metaCollector[ID][TYPE_SLOT])
	{
		if (sender != record.first)
			disconnect(sender, signal_str.c_str(), record.first, record.second.c_str());
	}
	m_metaCollector[ID][TYPE_SIGNAL].remove(std::make_pair(sender, signal_str));
}

//.............................................................................

void ObjectsConnector::registerMetaType(const QString &ID, const std::string &metaType, const std::pair<const QObject*, const std::string> &metaPair)
{
	m_metaCollector[ID][metaType].insert(m_metaCollector[ID][metaType].end(), metaPair );

	connect(metaPair.first, &QObject::destroyed, [=]()
	{
		m_metaCollector[ID][metaType].remove(metaPair);
	});
}
