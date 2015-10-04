#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QList>

#include "Player/playlistitemdata.h"

QList<PlaylistItemData> GetPlaylistFromJSON(const QString& jsonString);

#endif // PLAYLISTCONTROLLER_H
