// Exercise 15.31:
/*
 Given that s1, s2, s3, and s4 are all strings, determine what objects are created in the following expressions:
 (a) Query(s1) | Query(s2) & ~ Query(s3);
 (b) Query(s1) | (Query(s2) & ~ Query(s3));
 (c) (Query(s1) & (Query(s2)) | (Query(s3) & Query(s4)));
*/

//
//                         (s1)
//                      WordQuery
//                         X
//                        /
//         Query      OrQuery       (s2)
// (a) q =   X    =>    X X      WordQuery
//                          \       X
//                          X X    /
//                        AndQuery
//                                 \
//                                  X
//                                NotQuery -- X -> WordQuery (s3)
//


// >> same again
//
//                         (s1)
//                      WordQuery
//                         X
//                        /
//         Query      OrQuery       (s2)
// (a) q =   X    =>    X X      WordQuery
//                          \       X
//                          X X    /
//                        AndQuery
//                                 \
//                                  X
//                                NotQuery -- X -> WordQuery (s3)
//


//
//                            (s4)
//                         WordQuery
//                           X
//                          /
//                      AndQuery ---- X -> WordQuery (s3)
//                       X X
//                       /
//         Query      OrQuery
// (c) q =   X    =>    X X
//                        \
//                        X X            (s2)
//                      AndQuery -- X -> WordQuery
//                           \
//                            X
//                          WordQuery
//                            (s1)
//
