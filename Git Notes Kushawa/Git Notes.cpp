Git Notes:


Git Ignore:
    A .gitignore file is a text file that tells Git which files and directories to ignore in your project. 
    These ignored files are not tracked, staged, or committed to your repository.

Working:
    Create a file named .gitignore in your projects root directory
    Add patterns for files/folders you want Git to ignore
    Git will automatically exclude these files from tracking

Ex:
*.css
    all the files with .css extension will be ignored
passwords/
    all the files in the passwords folder will be ignored

Git Restore:
    It is used to discard unstaged changes in your working directory and go back to the last committed state of the file.
    It can also be used to unstage files from the staging area without discarding changes.

Scenario 1: You modified a file but want to discard the changes
    # Before: file is modified in working directory
    git restore myfile.py
    # After: file is restored to last committed version

Scenario 2: You accidentally staged a file you didnt want to commit
    # Before: file is in staging area
    git restore --staged myfile.py
    # After: file is unstaged but changes are kept in working directory

Scenario 3: You want to completely reset a file (unstaged changes + unstage)
    # Two-step process
    git restore --staged myfile.py  # First, unstage
    git restore myfile.py           # Then, discard changes

Git Reset:
    It is used to undo the changes or going back to the previous commit 
    It moves the HEAD pointer to the previous specified commit and delete all the commits after the specified commit.
    It can also modify the staging area and working directory based on the type of reset used.

Example:
    If your commit history looks like this:
    A -- B -- C -- D (HEAD)
    If you do git reset --hard B, Then your HEAD will be at B
    A -- B (HEAD)
    and C and D will be deleted forever from the commit history.

- Hard Reset: 
    `git reset --hard B` 
    HEAD moves to B, and all the changes after B are deleted

- Mixed Reset (default): 
    `git reset B` - 
    HEAD moves to B, changes after B are kept in unstaged area

- Soft Reset: 
    `git reset --soft B` 
    HEAD moves to B, changes after B are kept in staged area

Git Revert:
    It is used to undo the changes or going back to the previous commit 
    It does not delete the commits from the history, instead it creates a new commit and remove the changes done in the specified commit.
    It is a safe way to undo changes in a public branch because it undo the changes and preserves the commit history.
    git revert <commit-hash>

Example:
    If your commit history looks like this:
    A -- B -- C -- D (HEAD)
    If you do git revert D, Then your HEAD will be at E
    A -- B -- C -- D -- E (HEAD)
    and E will be a new commit and D changes will be removed.


git reset vs git revert:
    In git reset, 
    git reset --hard B means, all the changes after B will be deleted
    In git revert 
    git revert B means, B changes will be removed only 

