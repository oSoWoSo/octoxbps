/*
* This file is part of OctoXBPS, an open-source GUI for xbps.
* Copyright (C) 2020 Alexandre Albuquerque Arnt
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#include "packagetreeview.h"
#include <QTreeView>
#include <QHeaderView>
#include <QMouseEvent>

#include "settingsmanager.h"
#include "model/packagemodel.h"
#include "treeviewpackagesitemdelegate.h"

/*
 * This widget is the main package list tree view widget for Octopi
 */

PackageTreeView::PackageTreeView(QWidget *parent):QTreeView(parent)
{
}

/*
 * The necessary initialization settings
 */
void PackageTreeView::init()
{
  //ui->tvPackages->setAlternatingRowColors(true);
  setItemDelegate(new TreeViewPackagesItemDelegate(this));
  setContextMenuPolicy(Qt::CustomContextMenu);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
  setAllColumnsShowFocus( true );
  setSortingEnabled( true );
  setIndentation( 0 );
  header()->setSortIndicatorShown(true);
  header()->setSectionsClickable(true);
  header()->setSectionsMovable(false);
  header()->setSectionResizeMode(QHeaderView::Interactive);
  header()->setDefaultAlignment( Qt::AlignLeft );
}

/*
 * Here we get all column sizes from the current Octopi Settings store
 */
void PackageTreeView::resizePackageView()
{
  setColumnWidth(PackageModel::ctn_PACKAGE_ICON_COLUMN,
                                 SettingsManager::getPackageIconColumnWidth());
  setColumnWidth(PackageModel::ctn_PACKAGE_NAME_COLUMN,
                                 SettingsManager::getPackageNameColumnWidth());
  //setColumnWidth(PackageModel::ctn_PACKAGE_VERSION_COLUMN,
  //                               SettingsManager::getPackageVersionColumnWidth());
  //setColumnWidth(PackageModel::ctn_PACKAGE_REPOSITORY_COLUMN,
  //               SettingsManager::getPackageRepositoryColumnWidth());
}

/*
 * Whenever user clicks left mouse button in the first column...
 */
void PackageTreeView::mouseReleaseEvent(QMouseEvent *event)
{
  QTreeView::mouseReleaseEvent(event);

  if ((event->button() == Qt::LeftButton) && (columnAt(event->pos().x()) == PackageModel::ctn_PACKAGE_ICON_COLUMN))
  {
    emit customContextMenuRequested(event->pos());
  }
}

/*
 * Whenever focus enters this widget
 */
void PackageTreeView::focusInEvent(QFocusEvent *event)
{
  Q_UNUSED(event)

  QModelIndex maux = currentIndex();
  scrollTo(maux, QAbstractItemView::PositionAtCenter);
  setCurrentIndex(maux);
}
