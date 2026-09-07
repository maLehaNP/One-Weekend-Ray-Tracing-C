#ifndef HITTABLE_LIST_H 
#define HITTABLE_LIST_H 

typedef struct {
  int n;
  Hittable objects[];
} HittableList;

/*void list_add(Hittable object) {
  
}*/

int hit_List(HittableList* list, const ray* r, double tmin, double tmax, HitRec* rec) {
  HitRec tempRec;
  bool hitAnything = false;
  double closest = tmax;
 
  int i;
  for (i = 0; i < list->n; ++i) {
    if (hit(&(list->objects[i]), r, tmin, closest, &tempRec)) {
      hitAnything = true;
      closest = tempRec.t;
      *rec = tempRec;
    }
  }

  return hitAnything;
}

#endif /* HITTABLE_LIST_H  */

