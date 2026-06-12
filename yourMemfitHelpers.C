/* ===========================================================================
 *
 * yourMemfitHelpers.C --
 *
 *
 * 1.0 / 17. Nov 15 (ws)
 * - from scratch
 *
 *
 * ===========================================================================
 */

#include "memfitHelpers.H"

#define MEM_SIZE         1000
#define MEM_MIN_ADDRESS  100
#define ALLOC_MAX        10



unsigned
firstFitAlloc( unsigned blockSize )
  {
  unsigned address = 0;
  int index = 0;

  for (int i = 0; i < freeList.size(); i++)
  {
    if (freeList[i].size >= blockSize){
      index = i;
      break;
    }
  }

  address = allocBlock( index, blockSize );
  if (address==0 || blockSize<=0) return 0;
  
  return address;
};

unsigned 
nextFitAlloc(unsigned blockSize)
{
    static unsigned lastIndex = 0;

    for (unsigned k = 0; k < freeList.size(); ++k)
    {
        unsigned i = (lastIndex + k) % freeList.size();

        if (freeList[i].size >= blockSize)
        {
            unsigned address = allocBlock(i, blockSize);

            lastIndex = i;

            return address;
        }
    }

    return 0;
}


unsigned
bestFitAlloc( unsigned blockSize )
  {
  unsigned address = 0;
  int best_index = -1;
  
  for (int i = 0 ; i < freeList.size(); i++)
  {
      if (freeList[i].size >= blockSize)
      {
          if (best_index == -1 ||
              freeList[i].size < freeList[best_index].size)
          {
              best_index = i;
          }
      }
  }
  
  address = allocBlock(best_index, blockSize);
  if (address==0 || blockSize<=0) return 0;

  return address;
};


unsigned
worstFitAlloc( unsigned blockSize )
{
  unsigned address = 0;
  int worst_index = -1;

  for (int i = 0; i < freeList.size(); i++)
  {
      if (freeList[i].size >= blockSize)
      {
          if (worst_index == -1 ||
              freeList[i].size > freeList[worst_index].size)
          {
              worst_index = i;
          }
      }
  }
  
  address = allocBlock(worst_index, blockSize);
  if (address==0 || blockSize<=0) return 0;

  return address;
};


// int main(){
//   initHeap( MEM_MIN_ADDRESS, MEM_SIZE );

//   unsigned memRequest = 2;  //(rand() % ALLOC_MAX) + 1;
//   unsigned address = worstFitAlloc(memRequest);
//   std::cout << "Adress 1 : " << address << std::endl;
//   std::cout << "Adress 0 : " << freeList[0].address << std::endl;

//   std::cout << "allocated = " << address << '\n';

//   for (auto &b : freeList)
//   {
//       std::cout << "free: addr=" << b.address
//                 << " size=" << b.size << '\n';
//   }

//   address = worstFitAlloc(memRequest);
//   std::cout << "Adress 2 : " << address << std::endl;

  
//   address = worstFitAlloc(memRequest);
//   std::cout << "Adress 3 : " << address << std::endl;


//   address = worstFitAlloc(memRequest);
//   std::cout << "Adress 4 : " << address << std::endl;
// }
