#pragma once

#include <map>
#include <list>
#include <string>
#include <utility>

#include <QObject>

/**
 * @brief Позволяет устанавливать связь сигнал/слот между объектами ничего не знающими друг о друге.
 * Предназначен в первую очередь для соединения объектов расположенных "далеко" друг от друга.
 * @attention Сигнал/слот от одного и того же объекта НЕ соединяет!!!
 */
class ObjectsConnector : public QObject
{
	Q_OBJECT

public:
	/**
	 * Конструктор.
	 * Нужен для нормального использования этого класса в качества параметра в шаблонах и для протаскивания в QML (поэтому так же наследник QObject).
	 * Смысловой нагрузки не несет, класс выполнен а-ля Singleton, работает основываясь на статических полях и методах.
	 * @param parent - при необходимости можно привязать управление жизненным циклом к другому Qt объекту.
	 */
	explicit ObjectsConnector(QObject *parent = 0);

private:
	/// Конструктор копирования; без реализации.
	ObjectsConnector(const ObjectsConnector &);
	/// Оператор присваивания; без реализации.
	ObjectsConnector& operator=(const ObjectsConnector &);

public:
	/**
	 * Регистрирует сигнал с указанным идентификатором.
	 * @param[in] ID - идентификатор для установления связи.
	 * @param[in] sender - объект, высылающий сигнал.
	 * @param[in] signal - собственно сам сигнал.
	 */
	Q_INVOKABLE static void registerEmitter(const QString &ID, QObject *sender, const QString &signal, bool queued = false);
	/**
	 * Регистрирует слот с указанным идентификатором.
	 * @param[in] ID - идентификатор для установления связи.
	 * @param[in] receiver - объект, принимающий сигнал.
	 * @param[in] slot - метод, обрабатывающий сигнал.

	 */
	Q_INVOKABLE static void registerReceiver(const QString &ID, QObject *receiver, const QString &slot, bool queued = false);

	/**
	 * Разрегистрирует слот с указанным идентификатором.
	 * @param[in] ID - идентификатор для разрушения связи.
	 * @param[in] receiver - объект, принимающий сигнал.
	 * @param[in] slot - метод, обрабатывающий сигнал.

	 */
	Q_INVOKABLE static void unregisterReceiver(const QString &ID, QObject *receiver, const QString &slot);

	/**
	 * Разрегистрирует сигнал с указанным идентификатором.
	 * @param[in] ID - идентификатор для разрушения связи.
	 * @param[in] sender - объект, высылающий сигнал.
	 * @param[in] signal - собственно сам сигнал.
	 */
	Q_INVOKABLE static void unregisterEmitter(const QString &ID, QObject *sender, const QString &signal);

private:
	/**
	 * Регистрирует пару (мета объект Qt, прототип сигнала/слота).
	 * @param[in] ID - идентификатор для установления связи.
	 * @param[in] metaType - тип, определяющий сигнал или слот.
	 * @param[in] metaPair - пар объектов: первый - мета объект Qt, второй - прототип сигнала/слота.
	 */
	Q_INVOKABLE static void registerMetaType(const QString &ID, const std::string &metaType, const std::pair<const QObject*, const std::string> &metaPair);

private:
	/**
	 * Описание набора и способа хранения зарегистрированных сигналов/слотов.
	 * Ключ 1 - идентификатор для установления связи (ID).
	 * Ключ 2 - сигнал/слот.
	 * Список пар объектов: первый - мета объект Qt, второй - прототип сигнала/слота.
	 */
	typedef std::map<QString, std::map<std::string, std::list<std::pair<const QObject*, const std::string> > > > MetaObjectsMap;
	/// набор зарегистрированных сигналов/слотов.
	static MetaObjectsMap m_metaCollector;
};
