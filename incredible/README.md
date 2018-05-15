Incredible Computation Graph
--------------------------------------
A unit-based computation graph library. Each unit has its own
inputs, outputs and corresponding operations. By running a unit,
it does the following:
```
 +------+--------------------+
 | unit |                    |
 +------+                    |
 |<INPUT> => [OP] => <OUTPUT>|
 +---------------------------+
```

A unit can shared data via inputs or outputs

```
 +------+--------------------+
 | unit1|                    |
 +------+                    |
 |<INPUT> => [OP] => <OUTPUT>|
 +----------------------\  /-+
                         ||
 +------+----------------\/--+
 | unit2|                    |
 +------+                    |
 |<OUTPUT> <= [OP] <= <INPUT>|
 +---------------------------+

```
