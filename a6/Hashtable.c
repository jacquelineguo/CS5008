#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable_easy.h"

void PrintHashtable(Hashtable ht) {
   if (ht != NULL) {
    int i;
    for (i = 0; i< ht->num_buckets; i++) {
      LinkedList ll = ht->buckets[i];
      if (ht->buckets[i] != NULL) {
        LLIter iter = CreateLLIter(ll);
        do {
          HTKeyValue *payloadPtr;
          payloadPtr = NULL;
          LLIterGetPayload(iter,(void*) &payloadPtr);
         
          if (payloadPtr != NULL)
            printf("%s, ", payloadPtr->value);
        } while(LLIterNext(iter) == 0);
        if (iter != NULL && iter->cur_node != NULL)
          printf("\n");
        DestroyLLIter(iter);
        iter = NULL;
      }
    }
  }
}

Hashtable CreateHashtable(int num_buckets) {
  Hashtable ht;
  if (num_buckets <= 0) {
    return NULL;
  }
  ht = (Hashtable) malloc(sizeof(struct hashtableInfo));
  if (ht == NULL) {
    return NULL;
  }
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht ->buckets = (LinkedList *) malloc(num_buckets * sizeof(LinkedList));
  if (ht->buckets == NULL) {
    free(ht);
    return NULL;
  }
  int i;
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = CreateLinkedList();
    if (ht->buckets[i] == NULL) {
      int j;
      for (j = 0; j<i; j++) {
        DestroyLinkedList(ht->buckets[j]);
      }
      free(ht);
      return NULL;
    }
  }
  return (Hashtable) ht;
}

void DestroyHashtable(Hashtable ht, ValueFreeFnPtr value_free_function) {
  int i;
  for (i = 0; i < ht->num_buckets; i++) {
    LinkedList ll = ht->buckets[i];
    HTKeyValue *KV;
    while (NumElementsInLinkedList(ll) > 0) {
      value_free_function(KV->value);
      free(KV);
    }
    DestroyLinkedList(ll);
  }
  free(ht->buckets);
  free(ht);
}

int PutInHashtable(Hashtable ht, HTKeyValue kvp, HTKeyValue *old_kvp){
  LinkedList ll;
  uint32_t i = kvp.key % ht->num_buckets;
  ll = ht->buckets[i];
  HTKeyValuePtr newnodePtr = (HTKeyValuePtr) malloc(sizeof(HTKeyValue));
  if (newnodePtr == NULL) {
    return 1;
  }
  newnodePtr->key = kvp.key;
  newnodePtr->value = kvp.value;
  int res = 0;
  LLIter iter = CreateLLIter(ll);
  if (iter != NULL) {
    do {
      HTKeyValue *payloadPtr;
      payloadPtr = NULL;
      LLIterGetPayload(iter, (void *) &payloadPtr);
      if (payloadPtr->key == kvp.key) {
        res = 2;
        ht->num_elements--;
      }
    } while(LLIterNext(iter) == 0);
    DestroyLLIter(iter);
    iter = NULL;
  }
  if (InsertLinkedList(ll, newnodePtr) == 0) {
    ht->num_elements++;
    //    printf("%s\n", newnodePtr->value);
    //printf("%s\n", ll->tail->payload->value);
  } else {
    free(newnodePtr);
    return 1;
  }
  return res;
}

int LookupInHashtable(Hashtable ht, uint64_t key, HTKeyValue *result) {
  uint32_t i = key % ht->num_buckets;
  LinkedList ll = ht->buckets[i];
  if (NumElementsInLinkedList(ll) == 0) {
    return -1;
  }

  LLIter iter = CreateLLIter(ll);
  if (iter == NULL) {
    return -1;
  }

  do {
    HTKeyValue *payloadPtr;
    payloadPtr = NULL;
    LLIterGetPayload(iter, (void*) &payloadPtr);
    if (payloadPtr->key == key) {
      *result = *payloadPtr;
      DestroyLLIter(iter);
      iter = NULL;
      return 0;
    }
  } while (LLIterNext(iter) == 0);
  DestroyLLIter(iter);
  iter = NULL;
  return -1;
}

int NumElemsInHashtable(Hashtable ht) {
  return ht->num_elements;
}

int RemoveFromHashtable(Hashtable ht, uint64_t key, HTKeyValue *junk_kvp) {
  uint32_t i = key % ht->num_buckets;
  LinkedList ll = ht->buckets[i];
  if (NumElementsInLinkedList(ll) == 0) {
    return -1;
  }
  LLIter iter = CreateLLIter(ll);
  if (iter == NULL) {
    return -1;
  }
  do {
    HTKeyValue *payloadPtr;
    payloadPtr = NULL;
    LLIterGetPayload(iter, (void *) &payloadPtr);
    if (payloadPtr->key == key) {
      *junk_kvp = *payloadPtr;
      free(payloadPtr);
      LLIterDelete(iter);
      DestroyLLIter(iter);
      iter = NULL;
      ht->num_elements--;
      return 0;
    }
  } while (LLIterNext(iter) == 0);
  DestroyLLIter(iter);
  iter = NULL;
  return -1;
}


uint64_t FNVHash64(unsigned char *buffer, unsigned int len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;
  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}


uint64_t FNVHashInt64(uint64_t makehash) {
  unsigned char buf[8];
  int i;
  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (makehash & 0x00000000000000FFULL);
    makehash >>= 8;
  }
  return FNVHash64(buf, 8);
}
