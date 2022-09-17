/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBREPCB_EDITOR_BOARDEDITORSTATE_H
#define LIBREPCB_EDITOR_BOARDEDITORSTATE_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "boardeditorfsm.h"

#include <librepcb/core/types/length.h>

#include <QtCore>
#include <QtWidgets>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/
namespace librepcb {

class Board;
class GraphicsLayer;
class LengthUnit;
class Point;

namespace editor {

class UndoCommand;

/*******************************************************************************
 *  Class BoardEditorState
 ******************************************************************************/

/**
 * @brief The board editor state base class
 */
class BoardEditorState : public QObject {
  Q_OBJECT

public:
  using Context = BoardEditorFsm::Context;

  // Constructors / Destructor
  BoardEditorState() = delete;
  BoardEditorState(const BoardEditorState& other) = delete;
  explicit BoardEditorState(const Context& context,
                            QObject* parent = nullptr) noexcept;
  virtual ~BoardEditorState() noexcept;

  // General Methods
  virtual bool entry() noexcept { return true; }
  virtual bool exit() noexcept { return true; }

  // Event Handlers
  virtual bool processAddDevice(ComponentInstance& component,
                                const Uuid& device,
                                const Uuid& footprint) noexcept {
    Q_UNUSED(component);
    Q_UNUSED(device);
    Q_UNUSED(footprint);
    return false;
  }
  virtual bool processImportDxf() noexcept { return false; }
  virtual bool processSelectAll() noexcept { return false; }
  virtual bool processCut() noexcept { return false; }
  virtual bool processCopy() noexcept { return false; }
  virtual bool processPaste() noexcept { return false; }
  virtual bool processMove(const Point& delta) noexcept {
    Q_UNUSED(delta);
    return false;
  }
  virtual bool processRotate(const Angle& rotation) noexcept {
    Q_UNUSED(rotation);
    return false;
  }
  virtual bool processFlip(Qt::Orientation orientation) noexcept {
    Q_UNUSED(orientation);
    return false;
  }
  virtual bool processSnapToGrid() noexcept { return false; }
  virtual bool processResetAllTexts() noexcept { return false; }
  virtual bool processRemove() noexcept { return false; }
  virtual bool processEditProperties() noexcept { return false; }
  virtual bool processAbortCommand() noexcept { return false; }
  virtual bool processKeyPressed(const QKeyEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processKeyReleased(const QKeyEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processGraphicsSceneMouseMoved(
      QGraphicsSceneMouseEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processGraphicsSceneLeftMouseButtonPressed(
      QGraphicsSceneMouseEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processGraphicsSceneLeftMouseButtonReleased(
      QGraphicsSceneMouseEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processGraphicsSceneLeftMouseButtonDoubleClicked(
      QGraphicsSceneMouseEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processGraphicsSceneRightMouseButtonReleased(
      QGraphicsSceneMouseEvent& e) noexcept {
    Q_UNUSED(e);
    return false;
  }
  virtual bool processSwitchToBoard(int index) noexcept {
    Q_UNUSED(index);
    return false;  // Do NOT allow switching board by default
  }

  // Operator Overloadings
  BoardEditorState& operator=(const BoardEditorState& rhs) = delete;

signals:
  /**
   * @brief Signal to indicate that the current tool should be exited
   *
   * This signal can be emitted by each state to signalize the FSM to leave
   * the current state and entering the select tool.
   */
  void requestLeavingState();
  void statusBarMessageChanged(const QString& message, int timeoutMs = -1);

protected:  // Methods
  Board* getActiveBoard() noexcept;
  PositiveLength getGridInterval() const noexcept;
  const LengthUnit& getDefaultLengthUnit() const noexcept;
  QList<GraphicsLayer*> getAllowedGeometryLayers(const Board& board) const
      noexcept;
  bool execCmd(UndoCommand* cmd);
  QWidget* parentWidget() noexcept;

protected:  // Data
  Context mContext;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace editor
}  // namespace librepcb

#endif