#include <QAbstractItemModel>

#include "listmodel.h"

ListModel::ListModel(ListItem *prototype, QObject *parent)
    : QAbstractListModel (parent), m_prototype(prototype)
{
}

ListModel::~ListModel()
{
    delete m_prototype;
    clear();
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

QVariantMap ListModel::get(int row)
{
    QHash<int,QByteArray> names = roleNames();
    QHashIterator<int, QByteArray> i(names);
    QVariantMap res;
    while (i.hasNext()) {
        i.next();
        QModelIndex idx = index(row, 0);
        QVariant data = idx.data(i.key());
        res[i.value()] = data;
        //cout << i.key() << ": " << i.value() << endl;
    }
    return res;
}

void ListModel::appendRow(ListItem *item)
{
    appendRows(QList<ListItem*>() << item);
}

void ListModel::appendRows(const QList<ListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
    foreach (ListItem *item, items) {
        connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
        m_list.append(item);
    }
    endInsertRows();
}

void ListModel::insertRow(int row, ListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);
    connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
    m_list.insert(row, item);
    endInsertRows();
}

bool ListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row < 0 || row >= m_list.size()) return false;
    beginRemoveRows(QModelIndex(), row, row);
    delete m_list.takeAt(row);
    endRemoveRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row < 0 || (row + count) >= m_list.size()) return false;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for(int i = 0; i < count; ++i) {
        delete m_list.takeAt(row);
    }
    endRemoveRows();
    return true;
}

ListItem *ListModel::takeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    ListItem *item = m_list.takeAt(row);
    endRemoveRows();
    return item;
}

ListItem *ListModel::find(const QString &id)
{
    foreach (ListItem* item, m_list) {
        if(item->id() == id) return item;
    }
    return nullptr;
}

QModelIndex ListModel::indexFromItem(const ListItem *item) const
{
    Q_ASSERT(item);
    for(int row = 0; row < m_list.size(); ++row) {
        if(m_list.at(row) == item) return index(row);
    }
    return QModelIndex();
}

int ListModel::indexFromId(const QString id)
{
    for (int i = 0; i < m_list.size(); ++i) {
        if(m_list.at(i)->id() == id) return i;
    }
    return -1;
}

void ListModel::clear()
{
    beginResetModel();
    qDeleteAll(m_list);
    m_list.clear();
    endResetModel();
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return m_prototype->roleNames();
}

void ListModel::handleItemChange()
{
    ListItem* item = static_cast<ListItem*>(sender());
    QModelIndex index = indexFromItem(item);
    if(index.isValid())
        return dataChanged(index, index);
}
