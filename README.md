Infinity
-----------------------------------------------------

Incredible
-----------------------
- Introduction
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
- Example

A formula

   y = (a + b) * (-c)

Represent the computation with units, it looks like this


 ```

 +------+    
 |input0|--+                
 +------+  |  +--------+    
           +->|unit_add|----+
 +------+  |  +--------+    |
 |input1|--+                |  +--------+  +------+
 +------+                   +->|unit_mul|->|output|
                            |  +--------+  +------+
 +------+    +-----------+  |
 |input2|--->|unit_negate|--+
 +------+    +-----------+

 ```

The graph accept stream data, each input changed, the output would be updated.
