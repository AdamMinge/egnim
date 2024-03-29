/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/project_file_system_proxy_model.h"
/* -------------------------------------------------------------------------- */

ProjectFileSystemProxyModel::ProjectFileSystemProxyModel(QObject* parent) :
  QSortFilterProxyModel(parent)
{

}

ProjectFileSystemProxyModel::~ProjectFileSystemProxyModel() = default;

bool ProjectFileSystemProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
  auto source_model = dynamic_cast<QFileSystemModel*>(sourceModel());
  if(source_model)
  {
    auto root_path = source_model->rootPath();
    auto source_index = source_model->index(source_row, 0, source_parent);
    auto source_path = source_index.data(QFileSystemModel::FilePathRole).toString();

    if (root_path == source_path)                                         return true;
    else if(!source_path.startsWith(root_path + QDir::separator()))    return false;
  }

  return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
