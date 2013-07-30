/*
Copyright (C) 2013  codemonkey85

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "mouseeventeater.h"
#include "frmboxes.h"
#include "pkmviewer.h"
MouseEventEater::MouseEventEater(QObject *parent) :
    QObject(parent)
{
}
extern box_obj * frmCurBox;
extern int frmCurBoxNum;
extern party_obj * frmParty;
pkmviewer * pview;
pokemon_obj * apkm = new pokemon_obj;
extern void * theSlot;
bool ispartypkm_ = false;
bool MouseEventEater::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouseEvent;
    QString theObjName;
    int slot = 0;
    theObjName = obj->objectName();
    slot = (atoi(theObjName.right(2).toStdString().c_str()))-1;
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        mouseEvent = static_cast<QMouseEvent *>(event);
        switch(mouseEvent->button())
        {
        case Qt::LeftButton:
            theSlot = obj;
            switch(theObjName.toStdString()[2])
            {
            case 'B':
                apkm = &(frmCurBox->pokemon[slot]);
                ispartypkm_ = false;
                break;
            case 'P':
                apkm = &(frmParty->pokemon[slot].pkm_data);
                ispartypkm_ = true;
                break;
            }
            if(apkm->species != 0)
            {
                pview->setWindowTitle(QString::fromStdWString(getpkmnickname(apkm)));
                pview->setPKM(apkm,frmCurBoxNum, ispartypkm_);
                pview->displayPKM();
                pview->show();
            }
            break;
        default:
            break;
        }
    default:
        return QObject::eventFilter(obj, event);
        break;
    }
    return false;
}
