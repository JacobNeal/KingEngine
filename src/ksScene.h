/********************************************************
* Class:            ksScene
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksScene.h
*
*   Overview:
*       Class that contains multiple transitions and
*       executes them in parallel.
*
********************************************************/

#ifndef KS_SCENE_H
#define KS_SCENE_H

#include "ksTransition.h"
#include <list>

template <typename T>
class ksScene
{
    public:
        //                         Constructors
        ksScene();
        
        //                         Methods
        void                       addTransition(ksTransition<T> transition);
        bool                       isDone();
        void                       update();
        
    private:
        //                         Members
        std::list<ksTransition<T>> m_transitions;
        int                        m_duration;
        int                        m_current_frame;
};

/********************************************************
*   ksScene
*
*   Initializes the scene duration to 0, until a transition
*   is added to the list.
********************************************************/
template <typename T>
ksScene<T>::ksScene()
    : m_duration(0), m_current_frame(0)
{ }

/********************************************************
*   addTransition
*
*   Add a transition to the list of transitions in this
*   scene.
********************************************************/
template <typename T>
void ksScene<T>::addTransition(ksTransition<T> transition)
{
    if (transition.getDuration() > m_duration)
        m_duration = transition.getDuration();
    
    // Add the transition to the list.
    m_transitions.push_back(transition);
}

/********************************************************
*   isDone
*
*   Returns whether or not the scene is finished
*   executing all contained transitions.
********************************************************/
template <typename T>
bool ksScene<T>::isDone()
{
    return m_current_frame >= m_duration;
}

/********************************************************
*   update
*
*   Call the update method of each transition in this
*   scene in parallel.
********************************************************/
template <typename T>
void ksScene<T>::update()
{
    if (m_current_frame < m_duration)
    {
        // Update each of the transitions in parallel.
        for (typename std::list<ksTransition<T>>::iterator iter = m_transitions.begin();
            iter != m_transitions.end(); ++iter)
        {
            iter->update();         
        }
        
        m_current_frame++;
    }
}

#endif