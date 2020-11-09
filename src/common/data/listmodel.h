#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class ListItem: public QObject {
  Q_OBJECT

public:
  ListItem(QObject* parent = nullptr) : QObject(parent) {}
  virtual ~ListItem() {}
  virtual QString id() const = 0;
  virtual QVariant data(int role) const = 0;
  virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
  void dataChanged();
};

class ListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ListModel(ListItem* prototype, QObject* parent = nullptr);
  ~ListModel();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  Q_INVOKABLE QVariantMap get(int row);

  void appendRow(ListItem* item);
  void appendRows(const QList<ListItem*> &items);
  void insertRow(int row, ListItem* item);
  bool removeRow(int row, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  ListItem* takeRow(int row);
  ListItem* find(const QString &id);
  QModelIndex indexFromItem( const ListItem* item) const;
  Q_INVOKABLE int indexFromId(const QString id);
  void clear();

  QHash<int, QByteArray> roleNames() const;

private slots:
  void handleItemChange();

protected:
  ListItem* m_prototype;
  QList<ListItem*> m_list;
};

#endif // LISTMODEL_H
