/********************************************************
* Class:            ksTransition
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksTransition.h
*
*   Overview:
*       Class that transitions between the state of
*       2 passed numeric value types over a given
*       frame duration.
*
********************************************************/

#ifndef KS_TRANSITION_H
#define KS_TRANSITION_H

template <typename T>
class ksTransition
{
    public:
        //                         Member functions
        ksTransition(T * state1, T state2, int duration);
        ksTransition(const ksTransition & copy);
        ksTransition & operator=(const ksTransition & rhs);
        
        //                         Methods
        int                        getDuration();
        void                       update();
        
    private:
        //                         Members
        T *                        m_first_state;
        T                          m_second_state;
        T                          m_delta_state;
        int                        m_duration;
        int                        m_current_frame;
};

/********************************************************
*   ksTransition
*
*   Initializes the transition between two numeric valued
*   states. The first is by pointer because this transition
*   object will actually be updating the passed value.
*
*   The second state represents the desired future value.
********************************************************/
template <typename T>
ksTransition<T>::ksTransition(T * state1, T state2, int duration)
    : m_first_state(state1), m_second_state(state2), m_duration(duration),
    m_current_frame(0)
{
    m_delta_state = m_second_state - *m_first_state;
}

/********************************************************
*   ksTransition(const ksTransition<T> & copy)
*
*   The copy constructor for ksTransition, just copies
*   all of the member variables into this instance.
*   No deep copy is necessary for this class.
********************************************************/
template <typename T>
ksTransition<T>::ksTransition(const ksTransition<T> & copy)
    : m_first_state(copy.m_first_state), m_second_state(copy.m_second_state),
    m_delta_state(copy.m_delta_state), m_duration(copy.m_duration), m_current_frame(copy.m_current_frame)
{ }

/********************************************************
*   operator=
*
*   The overloaded assignment operator for ksTransition, 
*   just copies all of the member variables into this 
*   instance.
*   No deep copy is necessary for this class.
********************************************************/
template <typename T>
ksTransition<T> & ksTransition<T>::operator=(const ksTransition<T> & rhs)
{
    m_first_state   = rhs.m_first_state;
    m_second_state  = rhs.m_second_state;
    m_delta_state   = rhs.m_delta_state;
    m_duration      = rhs.m_duration;
    m_current_frame = rhs.m_current_frame;
}

/********************************************************
*   getDuration
*
*   Return the frame duration of the transition.
********************************************************/
template <typename T>
int ksTransition<T>::getDuration()
{
    return m_duration;
}

/********************************************************
*   update
*
*   Update the transition between the two states by adding
*   a fraction of the difference between the two states
*   on each frame update.
********************************************************/
template <typename T>
void ksTransition<T>::update()
{
    // If the current frame is less than the duration
    // then increment the first state.
    if (m_current_frame < m_duration)
    {
        *m_first_state += m_delta_state / m_duration;
        
        // Update the current frame.
        m_current_frame++;
    }
}

#endif