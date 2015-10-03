/**
 * Cкопировать пример и заполнить его необходимыми идентификаторами.
 * Пример использования:
 * @code{.cpp}

 #include <QObject>
 #include <QString>

/// Макрос для добавления идентификаторов.
/// Автоматически генерирует объявление свойства и реализацию метода доступа, пригодные для использования в QML
#define ADD_PROPERTY(propName) \
Q_PROPERTY(QString propName READ propName CONSTANT)\
public: static QString propName() {return #propName;}

/// Набор уникальных идентификаторов для использования в ObjectsConnector, которые видно из QML
class ObjectsConnectorID : public QObject
{
    Q_OBJECT

    ADD_PROPERTY(My_property_ID1)
    ADD_PROPERTY(My_property_ID2)
    ADD_PROPERTY(My_property_ID3)

public:
    explicit ObjectsConnectorID(QObject *parent = 0) : QObject(parent) {}
};

 * @endcode
*/
