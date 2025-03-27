# Candle Maker's Firmware Repository - Hardware 

-----------------------------------------------
TO START WORKING ON YOUR OWN DEVELOPMENT BRANCH
-----------------------------------------------
If you haven't pulled yet:
- copy the link in github (click the clone button, click ssh and copy the link)
- go to your terminal where you want the repository folder to live
- type `git clone <link-you-copied-from-repository>`


Now, to go into the repository and make your branch off of main:
- `cd candle-maker-fw-sp25` to go into the folder
- you should be on main, but `git status` or `git branch` to see which branch you are on
  - if you are not on main, type `git checkout main` to go to main
- if you are now on main, type `git pull` to pull the latest changes from our online github repo (repository) and update you local main branch with them
- now that you have the latest changes from main, type `git branch name-of-your-branch` to make your branch
- verify your branch exists with `git branch` again, you should see the name in the list
- to go to your branch, type `git checkout name-of-your-branch` and again do `git status` or `git branch` to verify
- now, congrats, you are on your branch and you can create files and edit code

-----------------------------------------------
TO ADD YOUR CHANGES TO GITHUB
-----------------------------------------------
To push changes once you have made them:
- congrats, now you have changes that build and you are ready to push
- start with a classic `git status` to see your modified files and unstaged files
- for each file you want to add to the commit, type `git add <name_of_your_file>`
  - As a note, you can add multiple files with `git add <name_of_first_file> <name_of_second_file> <name_of_third_file>`
  - You can also do `git add .` to stage (add) ALL the files that are unstaged (all the files highlighted in red), BUT some of these we don't want to add because you only need them on your computer, so there is a file called `.gitignore` that **ignores** the files specified within it. To be safe though, probably just add files manually if you don't understand the .gitignore file yet
- great, now your files are added, so you can make a **commit**
- first check the `git log` (and q to exit) to see what the last commit was (this is just a good exercise to understand what's going on when you make a commit)
- now, to commit your changes, type `git commit -m "info here about what you changed"` (the -m is for message btw, but I'm pretty sure you always need it so not sure why it's a thing)
- now do `git log` again to see that your commit now exists as the most recent commit in the history
- but, your commit on this branch is still only on your computer, and you need it to get to the github repo online
- so `git push` will push your changes to the remote version of your branch (on github)
  - if your branch is new and github doesn't know about it yet, it will tell you that you need `git push --set-upstream origin <your-branch>`, you can just copy it into the terminal and `enter`


Cool, so now you can pull, make commits, check the log, and push like a true git wizard, please lmk if you have any questions and good luck!
