/**
  * Aybabtu - A decentralized LAN file sharing software.
  * Copyright (C) 2010-2011 Greg Burri <greg.burri@gmail.com>
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
  
#ifndef REMOTECONTROLMANAGER_REMOTECONNECTION_H
#define REMOTECONTROLMANAGER_REMOTECONNECTION_H

#include <QObject>
#include <QSharedPointer>
#include <QTcpSocket>
#include <QTimer>
#include <QList>

#include <Libs/MersenneTwister.h>

#include <google/protobuf/message.h>

#include <Protos/common.pb.h>

#include <Common/Uncopyable.h>
#include <Common/Network.h>
#include <Common/LogManager/Builder.h>
#include <Common/LogManager/IEntry.h>
#include <Common/LogManager/ILogger.h>
#include <Common/LogManager/ILoggerHook.h>
#include <Core/FileManager/IFileManager.h>
#include <Core/PeerManager/IPeerManager.h>
#include <Core/PeerManager/IGetEntriesResult.h>
#include <Core/UploadManager/IUploadManager.h>
#include <Core/DownloadManager/IDownloadManager.h>
#include <Core/NetworkListener/INetworkListener.h>
#include <Core/NetworkListener/ISearch.h>

namespace RCM
{
   class RemoteConnection : public QObject, Common::Uncopyable
   {
      Q_OBJECT
   public:
      RemoteConnection(
         QSharedPointer<FM::IFileManager> fileManager,
         QSharedPointer<PM::IPeerManager> peerManager,
         QSharedPointer<UM::IUploadManager> uploadManager,
         QSharedPointer<DM::IDownloadManager> downloadManager,
         QSharedPointer<NL::INetworkListener> networkListener,
         QTcpSocket* socket
      );
      ~RemoteConnection();

      void sendMessageToItself(const QString& message);

   signals:
      void deleted(RemoteConnection*);
      void chatMessageSent(const QString&);

   private slots:
      void refresh();
      void dataReceived();
      void disconnected();

      void newChatMessage(const Common::Hash& peerID, const Protos::Core::ChatMessage&);
      void searchFound(const Protos::Common::FindResult& result);

      void getEntriesResult(const Protos::Core::GetEntriesResult&);
      void getEntriesTimeout();

      void newLogEntry(QSharedPointer<const LM::IEntry> entry);

      void sendBadPasswordResult();

   private:
      bool readMessage();
      void send(Common::Network::GUIMessageType type, const google::protobuf::Message& message) const;
      void removeGetEntriesResult(const PM::IGetEntriesResult* getEntriesResult);

      QSharedPointer<FM::IFileManager> fileManager;
      QSharedPointer<PM::IPeerManager> peerManager;
      QSharedPointer<UM::IUploadManager> uploadManager;
      QSharedPointer<DM::IDownloadManager> downloadManager;
      QSharedPointer<NL::INetworkListener> networkListener;

      QSharedPointer<LM::ILoggerHook> loggerHook;

      QTcpSocket* socket;
      QTimer timerRefresh;

      Common::Network::MessageHeader<Common::Network::GUIMessageType> currentHeader;

      QList< QSharedPointer<NL::ISearch> > currentSearches;
      QList< QSharedPointer<PM::IGetEntriesResult> > getEntriesResults;

      MTRand mtrand;

      bool authenticated;

#ifdef DEBUG
      QSharedPointer<LM::ILogger> loggerRefreshState; // A logger especially for the state message.
#endif
   };
}
#endif
