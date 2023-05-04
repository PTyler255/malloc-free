# MALLOC & FREE

Recreation of the Malloc and Free memory management functions in C--which uses the name Palloc. Palloc creates and manages its own Heap 4096 bytes in size by default and can break up and allocate the memory accordingly based on "Worst Fit" (largest range of memory is broken up first). Free maintains memory address order and successfully merges neighboring unallocated blocks of memory both forwards and back. Running included executable runs the various tests included in ptests.c to showcase its capabilites as it walks through the 4096 bytes. Main functions included in palloc.c.

## Setup for Tests
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
