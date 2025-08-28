---------------------------------------------------------------------------------------------------------------------------------------------
Git Notes:
Its a version control system (VCS) that helps developers track changes in their code
---------------------------------------------------------------------------------------------------------------------------------------------

Repository:
It stores all the files and track all the changes

Local Repository:
Stored in the computer

Remote Repository:
Hosted on a server ( github, gitlab )
Used for backup and team collaboration

---------------------------------------------------------------------------------------------------------------------------------------------

WorkFlow:
Create a new repo -> Add files to staging -> Do Commit -> Push to GitHub:

---------------------------------------------------------------------------------------------------------------------------------------------

Basic Commands:

Create a Repo:
    git init

Add file to staging area:
    git add name.txt

Remove File from staging area:
    git restore --staged name.txt

Commit the changes:
    git commit -m "Message related to changes"

To see the status:
    git status

To see the commit logs
    git log

Stop tracking a file 
    git rm --cached name.txt

---------------------------------------------------------------------------------------------------------------------------------------------

How to Reset Git Repository: ( Going back to prev version ):

1: Soft Reset:
    git reset --soft 1fc0d7fed09230bb1dd8f8d71ab9f59ed830c87b
Remove all the commits upto the commit id
All the files will be in staging area

2: Reset:
    git reset 1fc0d7fed09230bb1dd8f8d71ab9f59ed830c87b
Remove all the commits upto the commit id
All the files will be unstaged

3: Hard Reset:
    git reset --hard 1fc0d7fed09230bb1dd8f8d71ab9f59ed830c87b
Remove all the commits upto the commit id
Delete all the files completely

4: Revert ( Best Approach ):
    git revert 23c938d68ba1ab17f814acb44b58c99d50bcbd1a
Give the hashcode of the commit you want to remove
Delete all the files after this commit ( including this commit )
But tracks the log and stays in history
So, you can revert the revert 

---------------------------------------------------------------------------------------------------------------------------------------------

Branches:
Branches allow you to work on different versions of your code simultaneously without affecting the main code

Command:
git branch	                                    : List all branches
git branch <name>	                            : Create a new branch 
git switch <branch>	                            : Switch to an existing branch.
git switch -c <new-branch>	                    : Create & switch to a new branch.
git branch -d <branch>	                        : Delete a branch (safe, checks for unmerged changes).
git branch -D <branch>	                        : Force delete (even if unmerged).
git branch -m <new branch name>                 : Rename the current branch
git branch -m <old branch> <new branch name>    : Rename any branch

---------------------------------------------------------------------------------------------------------------------------------------------

Push / Pull Commands:

git push origin <branch>	            : Push a local branch to remote.
git pull origin <branch>	            : Pull latest changes from a remote branch.
git fetch --all	                        : Fetch all remote branches.
git push origin --delete <branch>	    : Delete a remote branch.

---------------------------------------------------------------------------------------------------------------------------------------------

Merging:
git switch main             : Switch to target branch
git merge feature/login     : Merge feature into main

---------------------------------------------------------------------------------------------------------------------------------------------

Rebase:
git switch feature/login    : Switch to target branch
git rebase main             : Replay commits on top of main

---------------------------------------------------------------------------------------------------------------------------------------------

WorkFlow:
Create a new Branch -> add and commit new files -> push to remote -> Merge to main -> Delete temp branch

---------------------------------------------------------------------------------------------------------------------------------------------

Git Stash:
Git stash is used to save changes in your working directory so you can switch branches without committing incomplete work.

git stash                                       :   stash changes
git stash save "file1"                          :   name the stash
git stash list                                  :   list all the stash
git stash apply                                 :   apply all the stash 
git stash apply stash@{0}                       :   apply specific stash
git stash pop                                   :   apply the stash and delete it from stash list
git stash drop                                  :   delete latest stash or specific stash
git stash apply stash@{0} <branch-name>         :   apply specific stash to specific branch
git stash clear                                 :   delete all the stash
git fsck                                        :   locate the deleted stash and their hashcode
git stash store <stash hash>                    :   recover the stash to stash location

---------------------------------------------------------------------------------------------------------------------------------------------



git remote add origin <https key>
git push --force origin main
