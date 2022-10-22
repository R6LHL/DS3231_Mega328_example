/* 
* TaskManger.hpp
*
* Created: 19.02.2018 20:04:55
* Author: R6LHL
*/

#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <Arduino.h>

template <unsigned const char T_TASK_QUEUE_SIZE>
class TaskManager
{
	
	//variables
	 void (*(taskQueue_[T_TASK_QUEUE_SIZE]))(void);        // Array of function pointers
	 void (*delayedTasksQueue_[T_TASK_QUEUE_SIZE])(void);  // Array of function pointers
	 unsigned int taskDelaysQueue_[T_TASK_QUEUE_SIZE];   //
	 void (*(currentTask_))(void);						// Function pointer
	 
	public:
	
	TaskManager(void)
	{
		for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; i++)
		{
			taskQueue_[i] = 0;
			delayedTasksQueue_[i] = 0;
			taskDelaysQueue_[i] = 0;
		}
	}
	
	//functions
///////////////////////////////////////////////////////////////////////////////////////////////	
	void clearTasks_(void)
	{
		noInterrupts();
	
		for (byte i=0; i < T_TASK_QUEUE_SIZE; ++i)
		{
			taskQueue_[i] = 0;
			delayedTasksQueue_[i] = 0;
			taskDelaysQueue_[i] = 0;
		}
	
		currentTask_ = 0;
	
		interrupts();
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	void ProcessTaskQueue_(void)
	{
		noInterrupts();
	
		currentTask_ = taskQueue_[0]; // set taskQueue[0] to execute
	
		for (unsigned char i = 0; i < (T_TASK_QUEUE_SIZE-1); ++i)
			{
				taskQueue_[i] = taskQueue_[i+1];						// Shift taskQueue
			}
		
		interrupts();
	
		if (currentTask_ !=0)
		{
			currentTask_();
		}
		else return;
		// execute current task
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	void TimerTaskService_(void){						// This function must be called from timer interrupt handler
																	// So it haven't cli() and sei()
		for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; ++i)			// Check taskDelaysQueue for !=0 and decrement it
		{
			if (taskDelaysQueue_[i] != 0)
			{
				(taskDelaysQueue_[i])--;
			}
			else
			{
				for (unsigned char i1 = 0; i1 < T_TASK_QUEUE_SIZE; ++i1)		// If taskDelay == 0 - put task to TaskQueue at free place
				{
					if ((taskQueue_[i1] == 0) && (delayedTasksQueue_[i] !=0 ))	// ??But what if there are no free places???
					{
						taskQueue_[i1] = delayedTasksQueue_[i];
						delayedTasksQueue_[i] = 0;								// Delete Task from delayedTaskQueue
						taskDelaysQueue_[i] = 0;
						break;
					}
				}
			}	
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	void SetTask_(void(*f)(void), unsigned int t)
	  {
	
		  bool copy_detected = false;
	
		  noInterrupts();
		
		  for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; ++i)
		  {
			  if ((delayedTasksQueue_[i] == f) || (taskQueue_[i] == f)) //Check for copies
			  {
				  copy_detected = true;
				  break;
			  }
		  }
		
		  if (copy_detected == false)
		  {
			  for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; ++i)
			  {
				  if ((delayedTasksQueue_[i] == 0))
				  {	
					  delayedTasksQueue_[i] = f;
					  taskDelaysQueue_[i] = t;
					  break;
				  }
			  }
		  }
		
		  interrupts();
		
	  }
///////////////////////////////////////////////////////////////////////////////////////////////
	void DeleteTask_(void(*f)(void))
	{
	
		noInterrupts();
		
		if (currentTask_ == f)
		{
			currentTask_ = 0;
		}
		
		for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; ++i)
		{
			if (f == taskQueue_[i])
			{
				taskQueue_[i] = 0;
			}
			
			if (f == delayedTasksQueue_[i])
			{
				delayedTasksQueue_[i] = 0;
				taskDelaysQueue_[i] = 0;
			}
		}
		
		interrupts();
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	void ChangeTaskDelay_(void(*f)(void), unsigned int t)
	{
	
		noInterrupts();
		
		for (unsigned char i = 0; i < T_TASK_QUEUE_SIZE; ++i)
		{
			if (delayedTasksQueue_[i] == f)
			{
				taskDelaysQueue_[i] = t;
			}
		}
		
		interrupts();
	
	}
///////////////////////////////////////////////////////////////////////////////////////////////	
};



#endif //TASKMANAGER_HPP