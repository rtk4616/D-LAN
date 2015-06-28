/**
  * D-LAN - A decentralized LAN file sharing software.
  * Copyright (C) 2010-2012 Greg Burri <greg.burri@gmail.com>
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
  
#ifndef HASHCACHE_IHASHCACHE_H
#define HASHCACHE_IHASHCACHE_H

#include <QSharedPointer>

#include <Protos/common.pb.h>

#include <IRootEntry.h>

namespace HC
{
   class IHashCache
   {
   public:
      virtual ~IHashCache() {}

      /**
        * Load all known hashes from the path given by 'root.getPath()' into 'root'.
        * It will use the path + file size + file date to match the file and thus to provide the hashes.
        * During this call the hashe database will not change.
        */
      virtual void loadTo(IRootEntry& root) = 0;

      /**
        * Update the hashe database according the given root.
        */
      virtual void saveFrom(const IRootEntry& root) = 0;
   };
}
#endif
