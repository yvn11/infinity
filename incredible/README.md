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

Build example app
----------------------
By running

```
make -C incredible all
```
an incredible application will be generated in incredible/build.


Run example app
----------------------

The application accept stream data. Flush a sequence of numbers to it from shell

```
./incredible/build/incredible <<< "3 4 1 5 1 23 0 8 0";
```

Otherwise, manually input is also fine.

```
./incredible/build/incredible<ENTER>
... input incredible data ... 
```

