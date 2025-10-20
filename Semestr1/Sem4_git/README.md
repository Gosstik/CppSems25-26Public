# Семинар 11. Знакомство с git

`wd` &mdash; Working Directory

```bash
watch -c git log --graph --oneline --decorate --all --color=always
```

## Plan

- What is VCS?
- Types of VCS
- Basic concepts of `git`: what is commit, branch. How they are related. What info is stored in commit. Commits are immutable. Merges and rebases. `checkout`
- `reset`, `commit --ammend`
- Fetching files from other commits with `checkout`
- Merge conflicts (example with removing `README.md`, show conflict markers)
- `stash`
- How to remove changes from `working directory` and `index`:

```bash
# Get changes
git checkout -- <file> # form index to wd
git checkout HEAD -- <file> # from last commit to wd and index

# Remove changes (only for tracked files)
git reset HEAD -- <file> # remove file from index, but leave changed in wd
get reset --hard HEAD -- <file> # reset file to last commit state
```

- Examine `scco` example
- `git diff`
- Squash commit


## VCS

`VCS` (Version Control System) &mdash; software tools that help software teams manage changes to source code over time.

Main types of VSC:

- `local` &mdash; stores version history on a single machine. For one person only
- `centralized` &mdash; server is a single, central point of control. For every operation (commit, revert, ...) requires internet access
- `distributed` &mdash; spread data across multiple machines or locations. Each machine stores its own version and all history and can operate independently

Example of `centralized` VCS &mdash; `svn` (subversion).
Example of `distributed` VCS &mdash; `git`. One can develop without network connection.


## `git` objectives

- Store project development history
- Develop with team
- Integrate changes

- [git flow](https://cdn.hashnode.com/res/hashnode/image/upload/v1668069961266/fI6dAXt_8.png)

## Installation

```bash
sudo apt-get install git
```


## `git` CLI

!!! `NOTE`: every git command has `--help` flag (useful to recall flag names). Even more documentation is accessible with: `git help <command>`.

### TLDR

Basic commands:

```bash
# Create repository
git init

# Create branch
git checkout -b <branch>

# Just change current branch
git checkout <branch>

# Add changes to index
git add <file>

# Commit changes
git commit -m "<commit message>"

# Push changes to remote repository
git push -u origin <branch>

# Get updates from remote repository (when new tasks appear)
git pull origin <branch>
```


### Create repository

```bash
cd path/to/project
git init
git commit --allow-empty -m "initial commit"

# List files in project
tree -a
```


### Configuration

3 types of config:

1) `system` (`/etc/gitconfig)`) &mdash; for all users in system
2) `global` (`~/.gitconfig`) &mdash; user settings
3) `local` (`<project>/.git/config`) &mdash; project specific

```bash
cat ~/.gitconfig
cat .git/config

git config -l
git config --local -l
```

Basic configuration:

```bash
git config --global user.name "My Name"
git config --global user.email "mail@gmail.com"
git config --global core.editor /usr/bin/vim
touch "${HOME}/.gitignore"
git config --global core.excludesfile "${HOME}/.gitignore"

# To remove
git config --unset user.name
```

### Remote Repository

There are two types of `git` installations: server side and client side. `gitlab` and `github` give us UI for interacting with server side installation. To fetch data from them, we need to add them as `remote` repositories. That may be done with `git remote add <alias> <http_link>` command.

```bash
# Most cases
git remote add origin git@github.com:Gosstik/CppSems24-25Public.git

# We can add another remote with another alias
git remote add template git@github.com:Gosstik/CppSems25-26Public.git

# List existing remotes
git remote -v
```

You may actually do 2 things with remote repositories:

- `fetch` data &mdash; download it to your local machine
- `push` data &mdash; upload data to server

So each remote alias has two versions. You can change alias url for only `push`:

```bash
git remote set-url --push origin git@github.com:Gosstik/CppSems25-26Public.git
```

### ssh

Interaction between server and client may occur in different ways. Most common and widely used &mdash; `ssh` connection.

#### ssh key generation

- Create directory `mkdir -p ~/.ssh/github`.

- Generate ssh key with command (skip passphrase, use `/home/<user>/.ssh/github/key` as a path):

```bash
EMAIL=example@gmail.com
ssh-keygen -t ed25519 -C "${EMAIL}"
```

- Edit `~/.ssh/config`. Add to the end lines:

```bash
Host github.com
  HostName github.com
  PreferredAuthentications publickey
  IdentityFile ~/.ssh/github/key
```

- Create private repo and check you can clone it

Worse, but also possible to just modify `core.sshCommand` config:

```bash
git config core.sshCommand 'ssh -i path/to/the/key/privatkeyfilename'
git config --unset core.sshCommand # fallback
```

### `git` structure

Two phase system of storing changes:

- Working directory:
  - Untracked files
  - Changes not staged for commit
- Index
  - Changes to be committed
- Repository


```bash
# Show current state
git status

# Move files from Working directory to Index
git add <file>
git add .
git add -A

# Move files from Index to Repository
git commit
git commit -m "description"
git commit -am "description" #  ignores untracked files
git commit --allow-empty -m "initial commit"

# Change commit date
git show --pretty=fuller
git commit --author='My Name <join@me.com>' --date='2021-01-01 12:12:00'
```


### Commits

Atomicity. Here reset.

Commits in github: [github.com/git/git/commits/master](https://github.com/git/git/commits/master). See commit description.


### File modes

`644` &mdash; simple file
`755` &mdash; executable

In `Windows` permission for reading file is united with permission to execute it.

```bash
# Make all files to 644
git config core.fileMode false

git update-index --chmod=+x run.sh
git add --chmod=+x run.sh
```

### `.gitignore`

Add to configuration:

```bash
touch "${HOME}/.gitignore"
git config --global core.excludesfile "${HOME}/.gitignore"
```

Example of global `.gitignore` content: [global.gitignore](./gitignore/global.gitignore)

```bash
# --force
git add -f <file>
```

Supported patterns for `.gitignore`: [atlassian](https://www.atlassian.com/git/tutorials/saving-changes/gitignore).

!!! NOTE: if file has already been added to git, `.gitignore` will not help. You should directly remove it from git.

```bash
git rm -r --cached dir
# use -f carefully
# add changes to remote repo: add, commit, push
```


### `.gitkeep`

In order to add empty directory to `git`, one have to create empty `.gitkeep` file to it.


### Branches

#### Objectives

- Support feature
- Versioning

Branch &mdash; reference to commit. Commit has 40 hexadecimal digits.

```bash
git branch feature            # Create branch 'feature'
git branch feature master     # Create branch 'feature' on 'master' commit
git checkout feature          # Move to branch 'feature'
git checkout -b feature       # Create and move to branch

git branch -v

# Remove branch (commits will remain in git)
git branch -d feature # from local
git branch -D feature # from local, force
git push -d feature # from remote
```

`HEAD` &mdash; pointer to current commit or branch.


TODO: describe remote and local branch

### `git stash`

We are unable to `checkout` to another branch with **different versions** of files and **uncommitted changes**. But we can use `git stash`:

```bash
git stash push
git stash pop # can be applied on other branch, but may cause conflicts

```

TODO: stash info


### `git checkout`

```bash
git checkout master
git checkout -f master
git checkout -f HEAD # remove all unstaged changes

git checkout HEAD <file> # remove unstaged changes in file
git checkout HEAD~ <file> # get file preceding the last commit
git checkout @~ <file>
git checkout @~~~ <file>
git checkout @~3 <file>

git checkout <commit> # detached HEAD
```


### Merging and rebasing

#### `merge`

```bash
# Merge <branch> to master, creates merge commit
git checkout master
git merge <branch> -m "some message"

# Undo merge
git reset --hard HEAD~ # 1
git branch -f master <commit> # 2
```

Fast-forward merge is equivalent to:

```bash
git checkout -B master <branch>
```

#### `merge conflicts`

```bash
cat .git/MERGE_HEAD

git checkout master
git merge feature -m "some message" --log

git checkout --ours main.cpp
git checkout --theirs main.cpp
git checkout --merge main.cpp # show markers again
git checkout --conflict=diff3 --merge main.cpp

git add main.coo
git merge --continue # same as 'git commit'

git show # after fixing conflict
git show --first-parent
git diff HEAD^2 HEAD^
git diff HEAD^^ # same as 'git diff HEAD~~'

git merge --abort # same as 'git reset --merge'

git merge --no-commit feature # to avoid semantic conflicts

git merge --no-ff
git config merge.ff false

git merge --squash feature # only one parent
git merge --abort # will fail
```

TODO: types of merge

#### `rebase`

```bash
git checkout feature
git rebase master # move feature to master

git rebase [--continue|--abort|--quit|--skip]

# abort rebase
git reflog feature -1
git reset --hard feature@{1}

# Probably cherry-pick will be simpler
git rebase --onto master feature # rebase current branch on 'master' starting from 'feature' (feature commit is not included)
# --no-ff

git rebase --rebase-merges master
```

`rebase` must be used if only one person at a time works with branch. After rebase **force push** must be applied.

Interactive rebase:

```bash
git rebase -i master
# pick
# reword
# edit
# squash/fixup

git rebase -i @~5
```

TODO: autosquash


### `reset`

Commits are **immutable** in git, you cannot change them. To "rewrite" commits you can use `git reset`. There are three main types of reset:

1) hard
2) mixed
3) soft

hard:

```bash
# !!! WILL REMOVE UNCOMMITTED CHANGES
git reset --hard HEAD~
# try 'git commit' after it
```

soft (is used for "changing" last commits):

```bash
# will save index and wd, used to "change" the last commit
git reset --soft HEAD~
# do some changes ...
git commit -c ORIG_HEAD # use message from previous commit, but can change in editor
git commit -C ORIG_HEAD # do not open editor for changing commit message
git commit -C ORIG_HEAD --reset-author

# Amend (use for changing commit message)
git commit --ammend # reset + commit -c
git commit --ammend --reset-author --no-edit # --no-edit for -C
```

```bash
git reset --mixed @~ # same as 'git reset @~'

# Remove file from Index, but keep changes in wd
git reset <file>

# Rarely used --- add file to index (but not to wd) from specific commit
git reset <commit> <file>
```


### `cherry-pick`

Alternative: create nre branch, than merge it with others.

```bash
git cherry-pick <commit>
git cherry-pick -x <commit> # save info form base commit
git cherry-pick master..feature

git cherry-pick --continue
git cherry-pick --abort
git cherry-pick --quit # save applied commits

# Just apply changes without commit
git cherry-pick --no-commit feature # same as 'git cherry-pick -n'
```

### `revert`

Used as reset but in such situations, when code has been pushed to remote and other developers has already fetched changes.

```bash
git revert <commit>
git revert @
git revert @~3..@

# Revert merge commits (DANGEROUS)
git revert <commit> -m 1 # -m --- parent
```


### `log`, `reflog`, `show`

Options to get some information about repository.

#### `log`

```bash
git log --graph --oneline --decorate --all

git log --graph --oneline
git log --graph --oneline --no-decorate

# Print commits reachable from master and feature (default is HEAD)
git log master feature --graph --oneline
# Print commits, reachable from all branches
git log --all --graph --oneline

git log master..feature # changes in feature since branching out from master
git log feature ^master # same as above, more flexible
# --boundary --- show split commit
git log feature.. --boundary # differences in HEAD since feature

# symmetric difference
git log master...feature --boundary --graph
```

Search with `git log`:

```bash
git log --grep World # searches only from current brunch
git log --grep World feature

git log --grep Hello --grep World --all-match
git log --grep -P 'say(Hello|World)' #  -P to use perl pattern matching
git log -i --grep Hello # case insensitive


git config --global grep.patternType perl

# disable regex
git config -F ...

# Search commits with specific changes in file (flag -G)
git log -G'Hello, world' -p           # -p to show diff
git log -G'Hello, world' -p main.cpp  # select file

# Search for changes inside function
git log -L '/int main() {/,/^}/:main.cpp'

git log --author=Egor
git log --committer=Vashkevich
git log --before '3 month ago'
git log --after '2017-09-14 10:30:00 +03'
```

Customize format in `git log`:

```bash
git log --pretty=oneline --abbrev-commit # same as git log --oneline
# move %cd to %cr for relative date
git log --pretty=format:'%C(yellow)%h %cd %C(reset)| %C(dim green)%s%d %C(#667788)[%an]' --date=short
# help on 'strftime' for date formatters

# Save format
git config --global pretty.my format:'...'
git config --global format.pretty my # set by default
git log --pretty=my
```

#### `reflog`

`reflog` is stored in `.git/logs/HEAD`. `reflog` is not saved in remote repository. It is specific for each clone.

```bash
git reflog # HEAD by default
git reflog master
git reflog master -4 # last 4 lines
git reflog --date=iso # date instead number
# HEAD@{'<date>'}
git log --oneline -g # alias for git reflog

git branch prev HEAD@{3}

git checkout @{-3} # search in reflog 3-rd line with 'checkout'
git checkout - # checkout on previous branch
```

`reflog` configs:

```bash
gc.reflogExpire="90 days ago"
gc.reflogExpireUnreachable="30 days ago"
```


#### `show`

```bash
# show - for commit info
git show HEAD --pretty=fuller
git show --quiet
git show @~:main.cpp --pretty=fuller
git show master:main.cpp --pretty=fuller
git show :main.cpp --pretty=fuller # show version from index

# Search for commit by it description
git show :/CommitDescription
```


### `git diff`

Example of `git diff` (such diffs are named `hunks`):

```text
diff --git a/.clang-tidy b/.clang-tidy
index 23001bb..73df14c 100644   # checksum of file and mode
--- a/.clang-tidy
+++ b/.clang-tidy
@@ -5,6 +5,7 @@                 # 6 lines from 5 line in first version will change to 7 lines from 5 line in second version
 # Excluded:
 #        readability-magic-numbers,
 #        readability-identifier-length,
+#        modernize-use-nodiscard,
 Checks: '-*,
         clang-analyzer-*,
         performance-*,
```

Change some file and try yourself!

```bash
git diff # compares wd to Index
git diff HEAD # compares wd to HEAD
git diff --cached # compare Index to HEAD

# NOTE: in other git commands .. and ... has other meaning
git diff master..feature # same as 'git diff master feature'
git diff master...feature # changes in feature since branching out from master
git diff master feature -- main.cpp
git diff --name-only master feature -- main.cpp
git diff master:one.cpp feature:two.cpp
git diff --no-index path1 path2 # no git is required

git diff -U0 master feature main.cpp # cut unchanged code

git commit -v # shows diff, but it is not saved in commit message
```


### `git reset`


### Aliasing

```bash
git config --global alias.c 'config --global'
```


### Other

```bash
git --bare

# Add only some changes in file to Index
git add -p <file>

# mode = --[cached|deleted|others|ignored|stage|unmerged|killed|modified]
git ls-files <mode>

# add only files to delete
git add $(git ls-files --deleted)

# Remove untracked filed from project folder
# d --- remove directories
# x --- also remove files, ignored by .gitignore
# f --- force
git clean -dxf

git blame

# List local/remote/both branches containing the commit
git branch --contains <commit-hash>
git branch -r --contains <commit-hash>
git branch -a --contains <commit-hash>

# Find commit with specific name
git log --grep='^feature$'

# Find commits that changed occurrences <text> in files .js
git log -S"<text>" -- "*.js"
```


## Web UI

!!! TODO: добавление ssh ключа

- [github.com](https://github.com/) &mdash; for `open source` projects
- [gitlab.com](https://gitlab.com/users/sign_in) &mdash; for small-medium `proprietary` development
- [bitbucket.org](https://bitbucket.org/product/) &mdash; for medium-large `proprietary` development. Has integrations with atlassian products: jira (dashboard), confluence (rfc, docs), bamboo (CI/CD)


Projects visibility:

- private
- public


TODO:

- reviewer and assignee
- search across github

## Git CLI prompt

Use instruction from [bash-setup](https://github.com/Gosstik/bash-setup).


## Training and practice

Syntax has some differences with original `git`. The main goal of exercises &mdash; to learn basic concepts.

- [learngitbranching](https://learngitbranching.js.org/)
- [git-katas](https://github.com/eficode-academy/git-katas/blob/master/Overview.md#katas-that-solve-standard-problems)


## TODO

- [docs](https://git-scm.com/)
- `watch`

```bash
git push -u origin my_branch:remote_branch
```

