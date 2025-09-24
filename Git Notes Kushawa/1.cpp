
------------------------------------------------------------------------------------------------------------------------
Git Notes - Comprehensive Guide

Git is a distributed version control system (VCS) that enables developers to efficiently track, manage, and collaborate 
on code changes. It provides mechanisms for maintaining a complete history of project modifications, facilitating 
collaboration, and supporting workflows for both individuals and teams.

------------------------------------------------------------------------------------------------------------------------
Key Concepts:

- Repository: 
    A repository is a storage location for your project files and the entire history of their changes. 
    It can be local (on your computer) or remote (hosted on platforms like GitHub or GitLab).

- Local Repository:
    The version of the repository stored on your local machine. You can make changes, commit, and review history locally.

- Remote Repository:
    A repository hosted on a server, typically used for backup, collaboration, and sharing code with others.

------------------------------------------------------------------------------------------------------------------------
Basic Workflow:

1. Create a new repository.
2. Add files to the staging area (index).
3. Commit changes to the local repository.
4. Push commits to a remote repository for sharing and backup.

------------------------------------------------------------------------------------------------------------------------
Essential Git Commands:

- Initialize a repository: 
    `git init` - Sets up a new Git repository in your project directory.

- Add files to staging area: 
    `git add <filename>` - Stages changes for the next commit.

- Remove files from staging area: 
    `git restore --staged <filename>` - Unstages files without discarding changes.

- Commit changes: 
    `git commit -m "commit message"` - Saves staged changes to the repository with a descriptive message.

- View status: 
    `git status` - Shows the current state of the working directory and staging area.

- View commit history: 
    `git log` - Displays a log of all commits in the repository.

- Stop tracking a file: 
    `git rm --cached <filename>` - Removes a file from version control but keeps it in your working directory.

------------------------------------------------------------------------------------------------------------------------
Resetting and Reverting Changes:

- Soft Reset: 
    `git reset --soft <commit-hash>` - Moves HEAD to the specified commit, keeping changes staged.

- Mixed Reset (default): 
    `git reset <commit-hash>` - Moves HEAD to the specified commit, unstaging changes but keeping them in the working directory.

- Hard Reset: 
    `git reset --hard <commit-hash>` - Moves HEAD to the specified commit and discards all changes after that commit.

- Revert: 
    `git revert <commit-hash>` - Creates a new commit that undoes the changes from the specified commit, preserving history.

Note: Revert is generally safer for undoing changes in shared repositories, as it maintains the commit history.

------------------------------------------------------------------------------------------------------------------------
Branching:

Branches allow parallel development by creating independent lines of work. This enables features, bug fixes, and experiments 
without affecting the main codebase.

- List branches: 
    `git branch`

- Create a new branch: 
    `git branch <branch-name>`

- Switch branches: 
    `git switch <branch-name>`

- Create and switch to a new branch: 
    `git switch -c <branch-name>`

- Delete a branch: 
    `git branch -d <branch-name>` (safe, checks for unmerged changes)
    `git branch -D <branch-name>` (force delete)

- Rename branches: 
    `git branch -m <new-name>` (current branch)
    `git branch -m <old-name> <new-name>` (any branch)

------------------------------------------------------------------------------------------------------------------------
Remote Operations:

- Push local branch to remote: 
    `git push origin <branch-name>`

- Pull latest changes from remote: 
    `git pull origin <branch-name>`

- Fetch all remote branches: 
    `git fetch --all`

- Delete a remote branch: 
    `git push origin --delete <branch-name>`

------------------------------------------------------------------------------------------------------------------------
Merging and Rebasing:

- Merging: 
    Combines changes from one branch into another. Typically, switch to the target branch and merge the feature branch.

    Example:
        `git switch main`
        `git merge feature/login`

- Rebasing: 
    Moves or reapplies commits from one branch onto another, creating a linear history.

    Example:
        `git switch feature/login`
        `git rebase main`

------------------------------------------------------------------------------------------------------------------------
Typical Branch Workflow:

1. Create a new branch for your feature or fix.
2. Add and commit changes.
3. Push the branch to the remote repository.
4. Merge the branch into the main branch.
5. Delete the temporary branch after merging.

------------------------------------------------------------------------------------------------------------------------
Git Stash:

Git stash temporarily shelves (or stashes) changes in your working directory so you can work on something else, 
then come back and re-apply them later.

- Stash changes: 
    `git stash` or `git stash save "description"`

- List stashes: 
    `git stash list`

- Apply stashed changes: 
    `git stash apply` (latest) or `git stash apply stash@{n}` (specific)

- Apply and remove stash: 
    `git stash pop`

- Delete a stash: 
    `git stash drop` (latest) or `git stash drop stash@{n}` (specific)

- Apply stash to a specific branch: 
    `git stash apply stash@{n} <branch-name>`

- Clear all stashes: 
    `git stash clear`

- Recover deleted stashes: 
    `git fsck` (find stash hash), `git stash store <stash-hash>`

------------------------------------------------------------------------------------------------------------------------
Remote Setup and Force Push:

- Add a remote repository: 
    `git remote add origin <repository-url>`

- Force push to remote (use with caution): 
    `git push --force origin main`

------------------------------------------------------------------------------------------------------------------------