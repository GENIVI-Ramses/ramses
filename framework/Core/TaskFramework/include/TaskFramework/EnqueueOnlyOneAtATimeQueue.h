//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------


#ifndef RAMSES_ENQUEUEONLYONEATATIMEQUEUE_H
#define RAMSES_ENQUEUEONLYONEATATIMEQUEUE_H

#include "PlatformAbstraction/PlatformLock.h"
#include "ITaskQueue.h"
#include "ITaskFinishHandler.h"
#include <deque>

namespace ramses_internal
{
    class TaskFinishHandlerDecorator;

    class EnqueueOnlyOneAtATimeQueue : public ITaskQueue, public ITaskFinishHandler
    {
    public:
        explicit EnqueueOnlyOneAtATimeQueue(ITaskQueue& nextQueue);
        virtual ~EnqueueOnlyOneAtATimeQueue();
        virtual Bool enqueue(ITask& Task) override;
        virtual void TaskFinished(ITask& Task) override;
        virtual void enableAcceptingTasks() override;
        virtual void disableAcceptingTasksAfterExecutingCurrentQueue() override;

    protected:
        ITaskQueue& m_nextQueue;
        std::deque<ITask*> m_waitingTasks;
        Bool m_hasOutstandingTask;
        PlatformLock mlock;
        Bool m_acceptingTasks;

    private:
        explicit EnqueueOnlyOneAtATimeQueue(const EnqueueOnlyOneAtATimeQueue&);
        void moveTaskToNextQueue(ITask& task);
    };
}

#endif
