# MALLOC & FREE
## Setup
> make

> ./palloc

##Tests

**Empty Heap:**
- Initializes the heap

**One Item:**
- Add an item to the heap

**-1 Item:**
- Remove an item from the heap and coalesce

**2 Items:**
- Add two things to the heap

**Free/Alloc/Free**
- Remove the first allocated pointer

**Worst Fit**
- Have something that could totally fit the first instance of empty space but doesn't

**Big Chunk**
- Get a bunch of bytes

**Big Gap**
- Having a large gap between allocated blocks

**Back Coalesce**
- Combine with a freeblock behind the newly freed space

**Slot in between**
- Allocate space between blocks

**Alloc to Alloc**
- Completely fill in a gap between allocations

**All the way to the end**
- Fill in the very end

**No more Room**
- Attempt to request space that doesn't exist

**Spotty**
- Have a list of alternating allocating/free blocks (also make sure everything is in order)
