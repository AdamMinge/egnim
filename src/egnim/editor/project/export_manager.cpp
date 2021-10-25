/* ----------------------------------- Local -------------------------------- */
#include "project/export_manager.h"
#include "project/export_template_list_model.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<ExportManager> ExportManager::m_instance = QScopedPointer<ExportManager>(nullptr);

ExportManager& ExportManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new ExportManager);

  return *m_instance;
}

void ExportManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

ExportManager::ExportManager() :
  m_export_template_model(new ExportTemplateListModel(this))
{

}

ExportManager::~ExportManager() = default;