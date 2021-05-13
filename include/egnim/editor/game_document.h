#ifndef GAME_DOCUMENT_H
#define GAME_DOCUMENT_H

/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document.h>
/* -------------------------------------------------------------------------- */

class GameDocument : public Document
{
  Q_OBJECT

public:
  explicit GameDocument(QStringView file_name, QStringView display_name, QObject* parent = nullptr);
  ~GameDocument() override;
};

#endif //GAME_DOCUMENT_H
