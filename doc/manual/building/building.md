# Building {#building}

Project have to be configured with `cmake` utillity.
Install it on you'r system. Then get the project sources.
To get the repo from github, you can execute the 
```
git clone https://github.com/Dolfost/tartan
```
To get ready for configuring step, execute next:

```
cd tartan
mkdir build 
cd build 
```
To configure a project, do the:
```
cmake -B . -S .. 
```
To actually build everything, you have to:
```
cmake --build .
```
To test the produced executables, run the `ctest` tool in the `build`
directory.
```
ctest 
```
## Results
The `tartan/build/` directory will contain next folders:
- `doc` Documentation of library. You can open html documentation by
 opening `tartan/build/doc/html/index.htm` in your browser.
- `board` Base board and piece API classes library (tt::Board, tt::Piece)
- `chess` Chess game implemented (tt::chess)