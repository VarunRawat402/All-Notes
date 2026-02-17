------------------------------------------------------------------------------------------------------------------------
Git Notes - Comprehensive Guide
------------------------------------------------------------------------------------------------------------------------

1. Repository: 
    → Where code is stored and tracked
    → Local Repository  - Exists on your computer
    → Remote Repository - GitHub, GitLab, Bitbucket

2. Working Folder:
    → The project folder where you create, edit, or delete files.

3. Staging Area:
    → A temporary area between the Working folder and the Local Repository.
    → It is where you prepare and organize which changes you want to include in your next commit.

Git Workflow:
    → Working Folder → Staging Area → Local Repository → Remote Repository

------------------------------------------------------------------------------------------------------------------------

Basic Git Commands:

1: 'git init'
2: 'git add <filename>' 
3: 'git add .'
4: 'git log'                               
5: 'git log --oneline'                     

------------------------------------------------------------------------------------------------------------------------

Branching:
    → A branch is a separate line of development
    → It lets you work on features, bug fixes, or development without changing the main code.

1: 'git branch'
    → Shows all branches

2: 'git branch user'
    → Creates a user branch 

3: 'git switch user'
    → Switch to user branch

4: 'git switch -c user'
    → Create user branch and switch to it

5: Delete a branch: 
    'git branch -d user'
        → Deletes only if user branch is already merged

    'git branch -D user'
        → Deletes user branch even if not merged

6: Rename branches: 
    'git branch -m <new-name>'
        → Rename current branch

    'git branch -m <old-name> <new-name>'
        → Rename any branch

------------------------------------------------------------------------------------------------------------------------

Remote Repositories Operations:


1: 'git remote add origin <repository-url>'
    → Link Github repo to local 

2: 'git clone <repository-url>'
    → Init git + Link github repo to local + download all code

3: 'git push origin main'
    → Push changes to main branch

4: 'git pull origin main'
    → Pull changes from main branch + merge them

5: 'git fetch origin main'
    → Fetch changes from main branh + No Merging

6: 'git fetch --all'
    → Downloads updates from remote
    → Does NOT merge automatically
    → Used when you want to review changes first

7: 'git push origin --delete <branch-name>'
    → Removes branch from the remote repository

------------------------------------------------------------------------------------------------------------------------

Merging and Rebasing:

- Merging: 
    → combines one branch into another.
    → Switch to the branch that should receive changes
    → Merge the feature branch into it

Example:
    `git switch main`
    `git merge feature/login`

- Rebasing: 
    → moves your branch commits on top of another branch.
    → Switch to the branch you want to update
    → Reapply its commits on top of the target branch
    → Mostly used for local or personal branches.

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

Git Ignore:
    → It is a file in which we add all the files we dont want git to TRACK, STAGE, COMMIT in repository
    → Common use: logs, build files, passwords, environment configs.

Ex:

1: '*.css'
    → Ignore all .css files

2: 'passwords/'
    → Ignores all files inside the passwords directory
    
Note:
→ Git does not affect files which are already tracked
→ To ignore the file which is already tracked
→ 'git rm --cached <filename>'

------------------------------------------------------------------------------------------------------------------------

Git Restore:
    → It is used to remove the changes and going back to last commit 
    → It is also used to unstage the staged files
    → File Level

Scenario 1: Remove Changes: 
    → 'git restore myfile.py'
    → You updated a file but changes are bad 
    → It will remove all the changes till last commit 

Scenario 2: You staged a file by mistake:
    → 'git restore --staged myfile.py'
    → File is removed from staging area

Scenario 3: Completely Reset a File:
    → 'git restore --staged myfile.py'   # Unstage
    → 'git restore myfile.py'            # Discard all recent changes
    → File becomes exactly like the last commit

------------------------------------------------------------------------------------------------------------------------

Git Reset:
    → It is used to undo the changes and going back to prev commit 
    → It moves the HEAD pointer from the current commit to specified commit
    → Delete of commits after specified commit depends on reset type
    → It erases the history of commits
    → Use reset only in local not when commit is pushed to remote
    → Uses:
        → You accidently commited or forget some files so want to remove the commit and commit again
        → You commit and something broke, now back to prev commit with no history

Commit History:

→ A -- B -- C -- D (HEAD)   →   'git reset --hard B'    →   A -- B (HEAD)
Commits C and D are removed from this history

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
    → It is used to undo the changes and going back to prev commit 
    → It does not delete the commits from history
    → It creates a new commit and remove the changes from the specified commit 
    → It is a safe way to undo changes in a public branch because it undo the changes and preserves the commit history.
    → 'git revert <commit-hash>'

A -- B -- C -- D (HEAD)     'git rever D'     →     A -- B -- C -- D -- E (HEAD)

D's changes will be removed 


------------------------------------------------------------------------------------------------------------------------