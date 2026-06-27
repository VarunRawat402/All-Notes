------------------------------------------------------------------------------------------------------------------------
Git Notes:
------------------------------------------------------------------------------------------------------------------------

Basic Git Commands:

1: 'git init'
2: 'git add <filename>' 
3: 'git add .'
4: 'git log'                               
5: 'git log --oneline'                     

------------------------------------------------------------------------------------------------------------------------

Branching:
    → Work on features/fixes without changing main code

1: 'git branch'                                 → Shows all branches

2: 'git checkout -b feature/loginPage'          → Creates feature branch 

3: 'git checkout feature/loginPage'             → Switch to feature branch

4: 'git branch -d user'                         → Deletes local branch if its merged

5: 'git branch -D user'                         → Deletes local branch even if its not merged

6: 'git branch -m <new-name>'                   → Rename current branch

7: 'git branch -m <old-name> <new-name>'        → Rename any branch

------------------------------------------------------------------------------------------------------------------------

Remote Repositories Operations:


1: 'git remote add origin <repository-url>'         → link local repo to GitHub

2: 'git clone <repository-url>'                     → clone repo + init + link (all in one)

3: 'git push origin dev'                            → Push changes to dev branch

4: 'git pull origin dev'                            → fetch + merge from dev branch

5: 'git fetch origin dev'                           → fetch only, no merge

6: 'git push origin --delete <branch-name>'         → delete branch from remote

------------------------------------------------------------------------------------------------------------------------

Merging and Rebasing:

- Merging: 
    → Combines one branch into another
    → Creates a merge commit → preserves full history

Example:
    'git checkout feature/loginPage'
    'git fetch origin'
    'git merge origin/dev'              // brings dev changes into feature branch

- Rebasing: 
    → Moves your commits on top of another branch
    → Temporarily removes your commits → updates branch → replays commits on top
    → Cleaner history (no merge commits) → linear history

Example:
    'git checkout feature/login'
    'git fetch origin'
    'git rebase origin/dev'

------------------------------------------------------------------------------------------------------------------------

Typical Branch Workflow:

1. 'git checkout -b feature/login'    → create feature branch
2. 'git commit'                       → make changes + commit work
3. 'git push origin feature/login'    → push to remote
4. 'git pull origin dev'              → merge after review
5. 'git branch -d feature/login'      → delete feature branch

feature → commit → push → PR/merge → delete

------------------------------------------------------------------------------------------------------------------------

Git Stash:
    → Temporarily saves uncommitted changes
    → Use when switching branches without committing

1. 'git stash'                        → save changes with no description
2. 'git stash save "description"'     → save with label

3. 'git stash list'                   → view all stashes

4. 'git stash apply'                  → apply latest stash, keeps stash
5. 'git stash apply stash@{n}'        → apply specific stash, keeps stash
6. 'git stash pop'                    → apply latest stash + delete it

7. 'git stash drop'                   → delete latest stash
8. 'git stash drop stash@{n}'         → delete specific stash
9. 'git stash clear'                  → delete ALL stashes

------------------------------------------------------------------------------------------------------------------------

Git Ignore:
    → Used to tells Git which files to NOT track, stage, or commit

Examples:
    *.css           → ignore all CSS files
    passwords/      → ignore entire passwords directory
    .env            → ignore environment file
    *.log           → ignore all log files
    
Note:
→ To ignore the file which is already tracked
→ 'git rm --cached <filename>'

------------------------------------------------------------------------------------------------------------------------

Git Restore:
    → It is used to Undo changes in local
    → It is also used to unstage the staged files
    → File Level

Scenario 1: Remove Changes: 
    → 'git restore application.yaml'

Scenario 2: You staged a file by mistake:
    → 'git restore --staged application.yaml'
    → File is removed from staging area

Scenario 3: Completely Reset a File:
    → 'git restore --staged application.yaml'   # Unstage
    → 'git restore application.yaml'            # Discard all recent changes

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

A -- B -- C -- D (HEAD)     'git revert D'     →     A -- B -- C -- D -- E (HEAD)

D's changes will be removed 


------------------------------------------------------------------------------------------------------------------------