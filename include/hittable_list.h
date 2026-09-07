#ifndef HITTABLE_LIST_H 
#define HITTABLE_LIST_H 

typedef struct {
  int n;
  Hittable objects[];
} HittableList;

/*void list_add(Hittable object)*/

bool hit_List(const HittableList* list, const ray* r, interval ray_t, HitRec* rec) {
  HitRec tempRec;
  bool hitAnything = false;
  double closest = ray_t.max;
 
  int i;
  for (i = 0; i < list->n; ++i) {
    interval inter = { ray_t.min, closest };
    if (hit(&(list->objects[i]), r, inter, &tempRec)) {
      hitAnything = true;
      closest = tempRec.t;
      *rec = tempRec;
    }
  }

  return hitAnything;
}

#endif /* HITTABLE_LIST_H  */

