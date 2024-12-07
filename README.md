# Tetris
## Project Guidelines
### Commit Convention
```
type(scope): description
```
#### Types
* API relevant changes
    * `feat` Commits, that adds or remove a new feature
    * `fix` Commits, that fixes a bug
* `refactor` Commits, that rewrite/restructure your code, however does not change any API behaviour
    * `perf` Commits are special `refactor` commits, that improve performance
* `style` Commits, that do not affect the meaning (white-space, formatting, missing semi-colons, etc)
* `test` Commits, that add missing tests or correcting existing tests
* `docs` Commits, that affect documentation only
* `build` Commits, that affect build components like build tool, ci pipeline, dependencies, project version, ...
* `ops` Commits, that affect operational components like infrastructure, deployment, backup, recovery, ...
* `chore` Miscellaneous commits e.g. modifying `.gitignore`

#### Scopes
The `scope` provides additional contextual information.
* Is an **optional** part of the format

### Project Structure
The project will be structured in directories following the convention above:
```
- \Tetris
    - .gitignore # Used for ignoring files in version control (e.g: \build)
    - README.md # This file
    - Makefile # Used to "automate" build process
    - \build # Contains the build files
    - \include # Contains all .hpp 
        - class_1.hpp
    - \src # Contains all .cpp
        - class_1.cpp
    - \lib # Contains external libraries
    - \docs # Contains documentation files
```

### Branching Strategy
The branching strategy will consist in 4 branch types:
* `main` The stable version of the project
* `develop` Branched from main. Merged into main when becomes a stable product.  
* `feature` Branched from develop for each feature in development. Merged into develop when finished.
* `hotfix` Branched from main to fix bugs. Merged into main when the bug is fixed. 


