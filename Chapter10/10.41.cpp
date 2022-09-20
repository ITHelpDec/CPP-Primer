// Exercise 10.41:
/*
 Based only on the algorithm and argument names, describe the oper- ation that the each of the following library algorithms performs:
 
 (1) replace(beg, end, old_val, new_val);
 >>  replace(ivec.begin(), ivec.end(), 1, 2);
 >>  replace all values in ivec that are 1 with 2
 
 (2) replace_if(beg, end, pred, new_val);
 >>  replace_if(ivec.begin(), ivec.end(), [] (const int &x) { return x % 2; } , 2);
 >>  provided the predicate is non-zero, replace all values in the container with the new value
 
 (3) replace_copy(beg, end, dest, old_val, new_val);
 >>  replace_copy(ivec.begin(), ivec.end(), il, 0, 1);
 >>  for every value in the container that is the old value, replace it the new container with the new value
 
 (4) replace_copy_if(beg, end, dest, pred, new_val);
 >>  replace_copy_if(ivec.begin(), ivec.end(), il, [] (const int &x) { return x % 2; } , 2);
 >>  as above, provided the predicate is non-zero
*/

