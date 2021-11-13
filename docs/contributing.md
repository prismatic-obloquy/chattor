# Contributors' Guide

So, you want to work on Chattor?
Awesome!
We appreciate the help.
There's a few ways to contribute, and all of them are greatly appreciated.

However, before you contribute:
Please make sure you're in the right place!
[The `chattor` repository][chattor-repo] can only help you with problems relating to the Chattor library, or the command-line reference client.
If it's one of the dependencies, we're still gonna have an issue open in the repo so we know to update the dependency when it's fixed, but we can't really fix the issue for you.
On the other hand, if it's something that depends on Chattor -- for example, a client -- we can't help, unless the bug traces back to an issue in Chattor.

That said, don't worry *too* much about it.
We'll help you figure out whether you're raising an issue in the right place.
We just don't want you to spend time writing up a good, detailed issue, only to be told we can't fix it.

Contributing more or less requires speaking English, at least for now.

## Bug reports

If you've found a security issue, [contact us privately][/contact] to get it fixed ASAP!

Bug reports are incredibly important.
Chattor, having been written by humans, is imperfect.
If you find something going wrong, even if it seems minor, it's worth fixing, and that means it's worth reporting.

There's [a nice form][bug-report] to file a bug report, which walks you through all the parts of a good bug report.
Keep in mind, though, that one person's bug is another's feature, and some things you might find irritating or confusing are intentional.
That doesn't mean the design is perfect, but it does mean you should consider whether it could have been intentional, and if it was, explain why it should be changed.

After the bug report is submitted, you'll probably get questions asking for some clarification.
Please respond as quickly as you can, so that people don't forget all about your bug report and need to re-read and re-understand it months later.
You'll probably also get comments between other contributors, talking about how to fix it.

## Feature requests

Chattor is more or less never done.
There's always new platforms to support, new features to add, and new conveniences to enable.
Not every feature is a good fit for Chattor, though, so [open a feature request][feature-request] and get some feedback.

First, while every feature request is appreciated, not every feature belongs in Chattor.
Some, like mentioned above, are just not relevant, because they belong in a dependency, or in other software that uses Chattor.
Others are just plain out of scope.
That said, we can't know if it's a good feature until you propose it, so please do!

If your feature fits, then it'll still probably need to be workshopped.
Expect to get a *lot* of feedback, pointing out problems and hopefully offering solutions.
You don't necessarily need to answer everything yourself, because once the feature is proposed it's the whole community's job to get it ready to implement or reject it.
That said, if you proposed the feature, you probably care about how it turns out, so you're encouraged to participate.

## Pull requests

Once a bug report or feature request has been talked about and clarified enough, it's ready for implementation.
For maintainers, that means creating a feature branch; for everyone else, it means forking the repository.
Then, before you make any changes, [make your pull request][pull-request].
Mark it as a draft at first, and start by just saying "Fixes #n", with the issue number instead of n.

As you work, update the pull request.
Treat it like a devlog, and don't be afraid to ask for help in it.
By the end, you should have a nice bullet-point list explaining the history of the pull request.
That helps people reviewing it understand why you made the decisions you did, and helps later contributors make their own decisions consistnt with past ones.

You should expect comments on it more or less anytime, but especially once you mark your pull request as ready.
Once you've addressed them, and no one else has comments, odds are good a maintainer has already approved the request and merged it.
If they haven't, ping one for help.

**Note**:
Please do *not* create a pull request unless there's a maintainer-approved issue it's addressing, or you're translating.
For example, if you find a bug and have an idea for how to fix it, please submit an issue with that information -- then, once it's approved, which should be pretty quick, you can put in your PR.
That gives the community a chance to see and discuss it, and might save you some effort if there's a better fix.

## Review

Reviewing bug reports, feature requests, and pull requests is extremely important to Chattor's well-being, because it ensures that fixes and updates actually get pushed through in a reasonably timely manner.
However, to review, you'll want to start by building a positive reputation.
Make some other kinds of (accepted) contributions.
Otherwise it's just a comment from some stranger saying it looks good.

While you're reviewing other people's work, be sure to:

- Be specific about criticisms or suggestions.
  If you can, point to specific line numbers.
  If it's a bug, give the best bug report you can.
- Don't suggest things that were already hashed out in the associated issue.
  The right place for that is the issue itself, not the PR implementing it.
- Write clearly and simply.
  Not every contributor will speak fluent English, and even if they do, tone is easily lost over text.
  Avoid sarcasm or irony, even if it's well-intentioned.

## Translation

Chattor is supposed to be for everyone, but not everyone can read English.
If you'd be willing to either translate the documentation and software into another language you speak, or review an existing translation, it'd be greatly appreciated.

The process is a bit different from other code or documentation updates.
You'll still start with an issue.
If there's [already one][language-search] for your language, comment that you'd like to help.
If not, [create one][language].
The issue you make will be deleted soon, and replaced with a full tracking issue for all the documentation that needs to be translated.
There'll be more instructions there.

## Auditing

The biggest gift you could give to Chattor is doing a proper code review.
It has a fairly extensive test suite, which is run under a memory sanitizer, but that's no guarantee that it's free from bugs.
An audit doesn't either, but having a fresh pair of eyes looking through and testing the code makes it more likely that any bugs will be caught.

If you want to do an audit, you can just clone the repo and get to work.
As you go through it, take detailed notes.
Find places where input comes in, and track down everywhere it can go out.
Write tests to poke at potential issues.
If you find anything severe, please [report it privately][/insecurity].
If it doesn't have security implications, please [report the bug][bug-report].
Even if you don't find anything, write it up anyway and post it.

Finally, once you're done and the writeup is posted, don't forget to let us know!
You can reach out to any maintainer, and we'll add it to the README.

  [/contact]: ./contact
  [bug-report]: https://github.com/prismatic-obloquy/chattor/issues/new?assignees=&labels=bug-report%2Cneeds-triage&template=BUG-REPORT.yml
  [feature-request]: https://github.com/prismatic-obloquy/chattor/issues/new?assignees=&labels=feature-request%2Cneeds-triage&template=FEATURE-REQUEST.ymll   [pull-request]: https://github.com/prismatic-obloquy/chattor/compare
