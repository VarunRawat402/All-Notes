------------------------------------------------------------------------------------------------------------------------
Git Notes - Comprehensive Guide
------------------------------------------------------------------------------------------------------------------------

1. Repository: 
    It is used by Git to store and tracks your project files and history.
    Local Repository - Exists on your computer
    Remote Repository - GitHub, GitLab, Bitbucket

2. Working Folder:
    The project folder where you create, edit, or delete files.

3. Staging Area:
    A temporary area between the Working Directory and the Local Repository.
    It is where you prepare and organize which changes you want to include in your next commit.

Git Workflow:
    Working Directory → Staging Area → Local Repository → Remote Repository

------------------------------------------------------------------------------------------------------------------------

Essential Git Commands:

1: Creates a new Git repository in the current folder:
    `git init`                              

2: Add files to staging area: 
    `git add <filename>`                    - add files to staging area
    `git add .`                             - stages all files

3: Remove files from staging area: 
    `git restore --staged <filename>`       - Removes file from staging, but keeps your code changes.
    `git restore <filename>`                - Removes all uncommitted changes in the working directory.

4: View commit history: 
    `git log`                               - detailed history
    `git log --oneline`                     - one line history

5: Stop Tracking a File (but keep it locally): 
    `git rm --cached <filename>`            - Removes file from Git tracking but file stays locally

------------------------------------------------------------------------------------------------------------------------

Branching:
A branch is a separate line of development
It lets you work on features, bug fixes, or experiments without touching the main code.

1: 'git branch'
Shows all local branches
Current branch is marked with *

2: 'git branch <branch-name>'
Creates a branch but does not switch to it

3: 'git switch <branch-name>'
Switch to specific branch

4: 'git switch -c <branch-name>'
Create branch and switch to it

5: Delete a branch: 
'git branch -d <branch-name>'
    Deletes only if branch is already merged
'git branch -D <branch-name>'
    Deletes branch even if not merged

6: Rename branches: 
'git branch -m <new-name>'
    Rename current branch

'git branch -m <old-name> <new-name>'
    Rename any branch

------------------------------------------------------------------------------------------------------------------------

Remote Operations:

1: 'git push origin <branch-name>'
Push changes to remote repositories

2: 'git pull origin <branch-name>'
Fetches changes from remote and merges them into your local branch

4: 'git fetch --all'
Downloads updates from remote
Does NOT merge automatically
Used when you want to review changes first

5: 'git push origin --delete <branch-name>'
Removes branch from the remote repository

------------------------------------------------------------------------------------------------------------------------

Merging and Rebasing:

- Merging: 
    combines one branch into another.
    Switch to the branch that should receive changes
    Merge the feature branch into it

Example:
    `git switch main`
    `git merge feature/login`

- Rebasing: 
    moves your branch commits on top of another branch.
    Switch to the branch you want to update
    Reapply its commits on top of the target branch
    Mostly used for local or personal branches.

Example:
    `git switch feature/login`
    `git rebase main`

------------------------------------------------------------------------------------------------------------------------

Typical Branch Workflow:

1. Create a feature branch
2. Make changes and commit
3. Push branch to remote
4. Merge into main
5. Delete the feature branch
feature → commit → push → merge → delete

Do NOT rebase a branch that others are using
Rebase only local / personal branches

------------------------------------------------------------------------------------------------------------------------

Git Stash:

Git stash temporarily saves your uncommitted changes 
Used when you need to switch branches quickly without committing.

1: 'git stash' or 'git stash save "description"'
Saves tracked file changes

2: 'git stash list'
View All Stashes

3: Apply stashed changes: 
'git stash apply'
'git stash apply stash@{n}'
    Applies stash but does NOT remove it

4: 'git stash pop'
Applies stash and deletes it

5: Delete a stash: 
'git stash drop'
'git stash drop stash@{n}'

6: 'git stash clear'
Deletes all stashed changes

------------------------------------------------------------------------------------------------------------------------

Remote Setup and Force Push:

1: 'git remote add origin <repository-url>'
Connects local repo to remote

2: 'git push --force origin main'
Overwrites remote branch history
Used after rebase or history rewrite

------------------------------------------------------------------------------------------------------------------------

Git Ignore:
    .gitignore tells Git which files or folders to not TRACK, STAGE, COMMIT in repository
    Common use: logs, build files, passwords, environment configs.

Working:
    Create a file named .gitignore in your projects root directory
    Add patterns for files/folders you want Git to ignore
    Git will automatically exclude these files from tracking

Ex:
*.css
    Ignore all .css files

passwords/
    Ignores all files inside the passwords directory
    
Note:
Git does not affect files which are already tracked
To ignore the file which is already tracked
'git rm --cached <filename>'

------------------------------------------------------------------------------------------------------------------------

Git Restore:
    Used to undo changes in files.
    Works in two places:
        Working Directory → discard changes
        Staging Area → unstage files

Scenario 1: Discard Unstaged Changes:
You edited a file but want to go back to the last commit
    'git restore myfile.py'
    Removes all changes
    File returns to last committed state

Scenario 2: Unstage a File (Keep Changes):
You staged a file by mistake
    'git restore --staged myfile.py'
    File is removed from staging area
    Changes stay in working directory

Scenario 3: Completely Reset a File:
Remove file from staging and discard all changes
    'git restore --staged myfile.py'   # Unstage
    'git restore myfile.py'            # Discard changes
    File becomes exactly like the last commit

------------------------------------------------------------------------------------------------------------------------

Git Reset:
    It is used to undo the changes or going back to the previous commit 
    It moves the HEAD pointer to the previous specified commit and delete all the commits after the specified commit.
    It can also modify the staging area and working directory based on the type of reset used.

Example:
    If your commit history looks like this:
    A -- B -- C -- D (HEAD)
    'git reset --hard B', Then your HEAD will be at B
    A -- B (HEAD)
    Commits C and D are removed from current history

Types of git reset:

1. Hard Reset:
    `git reset --hard B` 
    HEAD moves to B, Clears staging area, Discards all working directory changes

2. Mixed Reset (Default):
    `git reset B` - 
    HEAD moves to B, changes after B are kept in unstaged area

3. Soft Reset:
    `git reset --soft B` 
    HEAD moves to B, changes after B are kept in staged area

------------------------------------------------------------------------------------------------------------------------

Git Revert:
    It is used to undo the changes or going back to the previous commit 
    It does not delete the commits from the history, instead it creates a new commit that reverses the changes of the specified commit.
    It is a safe way to undo changes in a public branch because it undo the changes and preserves the commit history.
    'git revert <commit-hash>'

Example:
    If your commit history looks like this:
    A -- B -- C -- D (HEAD)
    If you do git revert D, Then your HEAD will be at E
    A -- B -- C -- D -- E (HEAD)
    and E will be a new commit and D changes will be removed.

------------------------------------------------------------------------------------------------------------------------