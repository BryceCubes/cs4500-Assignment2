# Queue, Array, and Map Implementation 

## **Queue:**
There are StrQueue and Queue, which supports String and Object respectively.
In order to increase effiency, we decide to make queue size to be finite(throw errors when exceed capacity).
Doing it this way, every time we perform pop operation, instead of shifting elements to left, we simply move head index(O(1)).
For push operation, simply push the element into the tail index of the queue, so it's constant time.
Making queue capacity finite is beneficial for push and pop operation, and the project description saying that we will use these two operations intensively. Since we trust it will push and pop frequently, having finite capacity is not a big concern (and users can set the capacity, too).
For StrQueue, in addition to functionalities provided by Queue, we also push pushing string, poping string and peeking string.
## Queue repository:
The documentation of queue was very confusing. The spec team documents the behavior of push and pop as stack(last in, first out). Moreover, their tests were also written that way.
In order to confirm the problem, I opened an issue in the spec team's repository. They responded very quickly (within 10 minutes) and fixed the tests right away.
The test coverage is thorough and our team don't need to write extra tests. Every method was tested and we have founded out (and fixed) several bugs in our code with the given tests.
The spec team was very easy to work with. Their documentation was very clear (after the update) and their tests covered the api thoroughly.

## **Array:**
In our design, we have 5 classes of array to support 5 data types: Object, String, bool, int, float.
Since bool, int, and float are primitives, we apply the technique autoboxing (borrowed from Java) so that eliminating the need to create internal pointers pointing to different data types and, thus, we don't need to write duplicate code.
Although all types now are objects, we do not allow mingling of different data types. For each subclass of Array, we carefully perform type checking on set and add method to make sure same type of elements are inserted into the queue. We also override the get, remove, append methods to guarantee same type is returned (i.e. StrArray.get() would return String*).
Unlike queue, array does not have limited capacity and it can grow as elements are added.
We made two decisions in for this api:
1. set method should only accept valid index (0 <= index < size). This is ambiguous because one of the tests from spec team has called an index not exist in the array.
2. append method should not modify current array. This is ambiguous because this method return an array pointer and did not mention whether to update current array. However, the test expects this method would update current array. We feel it's redundant having append method return an array pointer while updating current array. Therefore, we modified the test.
## Array repository:
The documentation of array has some ambiguity as it did not state the expected behavior of the methods. For example, append method returns an pointer to an array. However, the test for append method seems expect the array itself gets updated. The spec team did not document what is the expected behavior of this method.
The spec team was extremly hard to work with. I opened an issue one day ago and they replied me on the next day afternoon (so the average responding time is 1-2 days). Therefore, we made our own decisions in this api.
The tests were buggy (with typos and invalid parameters). For example, according to the signature, remove should take in an index. However, the test they wrote have string pointer as input. The test file itself cannot compile, and the team was not responsive at all. Therefore, we need to make our own decisions.
Most importantly, the tests only covered String. They did not cover int, float, and bool. We had asked for these tests and the spec team decided not to give out. Thus, we needed to write our own tests.

## **Map** 
### Map class
In our design for map, we focused on supporting the Object class which String extends. This means that the use of map can be extended to any new classes that extend Object. The map contains an Array of a custom Pair class, an allocated size value, and an element counter for the number of elements. Hashing the key value and storing it in a large Array of size 1024 to avoid having to rehash frequently. 

### Pair class
We created a Pair structure that has 3 fields: the key Object, the value Object, and a boolean that determines if the Pair is "null". This boolean was added so that when checking if a space in the map is being used, it can access this value to determine if an key and value has been updated. Otherwise this object is just a wrapper to keep the Objects paired together and handle the *hash()* and *equal()* methods. 

## Map Repository
The API for Map was fairly robust other than a few design choices that we wouldn't have made, but didn't have too much trouble implementing. We had hoped for a Map constructor that would take in a size_t to define the allocated size of the Map. Similarly, we would've appreciated a method for returning the allocated size of the map as well as the number of elements instead of only the latter.
Because it seems that this repo was used by many teams, any issues I ran into were already brought up and resolved by the team by the time I noticed. Their tests were not very exhaustive at first but they added some more tests as pull requests came in and were generally fairly responsive.

