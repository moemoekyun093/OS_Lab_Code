#include "rwlock.h"
#include <pthread.h>

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  //	Write the code for initializing your read-write lock.
  rw->reader_held=0;
  rw->writer_held=0;
  rw->ref=0;

}

void ReaderLock(struct read_write_lock * rw)
{
  //	Write the code for aquiring read-write lock by the reader.
      // while(1)
      // {
      //   pthread_mutex_lock(&rw->lock);
      //   if(rw->writer_held==1)
      //     pthread_mutex_unlock(&rw->lock);
      //   else
      //     break;

      // }
      pthread_mutex_lock(&rw->lock);
      while(rw->writer_held==1)
      {
        pthread_cond_wait(&rw->reader,&rw->lock);
      }
      rw->reader_held=1;
      rw->ref++;
      // cout<<rw->ref<<endl;
      pthread_mutex_unlock(&rw->lock);
      // cout<<"exit"<<endl;
      
    
  

}

void ReaderUnlock(struct read_write_lock * rw)
{
  //	Write the code for releasing read-write lock by the reader
  pthread_mutex_lock(&rw->lock);
  rw->ref--;
  // cout<<rw->ref<<endl;
  if(rw->ref==0)
    { 
      rw->reader_held=0;
      pthread_cond_broadcast(&rw->writer);
    }
  pthread_mutex_unlock(&rw->lock);
  cout<<"exit"<<endl;
}

void WriterLock(struct read_write_lock * rw)
{
  //	Write the code for aquiring read-write lock by the writer.
  // cout<<"entered"<<endl;
  pthread_mutex_lock(&rw->lock);
  while(rw->writer_held == 1 || rw->reader_held==1)
  {
      // cout<<"enter"<<endl;
      pthread_cond_wait(&rw->writer, &rw->lock);
      // cout<<"hehe"<<endl;
  }
  rw->writer_held=1;
  pthread_mutex_unlock(&rw->lock);
  cout<<"exited"<<endl;

}

void WriterUnlock(struct read_write_lock * rw)
{
  //	Write the code for releasing read-write lock by the writer.
   pthread_mutex_lock(&rw->lock);
   rw->writer_held=0;
   pthread_cond_broadcast(&rw->reader);
   pthread_cond_broadcast(&rw->writer);

   pthread_mutex_unlock(&rw->lock);

}
