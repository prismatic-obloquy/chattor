# Chattor v0.0.1

Chattor is an anonymized, distributed, and end-to-end encrypted chat system and social network.
It supports text chat, file transfer, and offline messages, all with public-key cryptography and as anonymous as you want yourself to be.
It's built on Tor's onion services, and gives back to the network by encouraging every user to run or sponsor a Tor relay too.
For more information, see `docs/` in the repo or [the website][chattor-clear-site] (also available in [onion][chattor-onion-site] form).

This repository is the reference implementation of [the Chattor protocol][website-protocol], as both a simple command-line client and a production-ready C library.
There are [plenty of clients][known-clients] and, if you want to make your own, [detailed documentation][api-docs] to help.

> **Security warning**:
>
> Chattor is not a security product; it's a privacy product.
> It lets you have a Facebook-like experience, without the Facebook-like tracking, and it tries pretty hard to make sure people can't know anything you don't post publicly, without your approval.
> *To accomplish this*, it provides some measure of security; namely, protections against unauthorized people being able to read messages or see relationships.
> However, it's ultimately meant to be a privacy-respecting social network, and while you may find it useful for other purposes, you should take a close look at [the protocol][website-protocol] to make sure it meets your needs.
>
> The cryptography is built on solid principles and with well-reviewed implementations of primitives.
> However, Chattor hasn't (*yet*) been audited, and may be misusing the cryptography, or making stronger guarantees than actually hold.
> I'm confident I did things right, and trust Chattor myself, but until *someone else* has gone in and thoroughly reviewed it, I can't ethically recommend you trust it too.
>
> Finally: Don't let this scare you into avoiding Chattor.
> Let it scare you into making your own reasoned, educated decision about it.
> It's your privacy.
> **You** should be in control.

## FAQ

There are some common questions regarding Chattor, so here are the answers.

If you have a question not on this list, please [ask][questions]!

### If you're not paying for the product, you *are* the product. I'm not paying for Chattor. So what's the product here?

There isn't one.

Most companies, including most privacy systems, have to support massive infrastructure and many employees.
Costs can get extremely high, and they need to pay *somehow* -- so they either need to sell something to you, like Proton; be a nonprofit, like Signal; or sell *you* to something, like Facebook.

But if you could eliminate all the costs, you wouldn't need any financial support at all.
That's Chattor's trick.

There's no infrastructure.
Everything is built over Tor, which already exists, and there's no central server passing messages around.
That immediately removes almost all the infrastructure costs.
All that remains is the website -- which doesn't actually play any part in making Chattor run; it's just one way to get the software.
Also, the website is $20 a month, and I can cover that out of pocket.

There are also no employees.
Everyone working on it is volunteering their time to it.
While this means we have slower turnaround time for bugs and features, it also means we don't need to come up with funding for any employees, so no one can threaten us by cutting funding off.

The end result is that there *is* no product here.
You don't need to worry about being it.

(Note this might not apply to your Chattor client -- expect them to provide their own guarantees.)

### What's stopping someone from just shutting Chattor down?

There's three potential readings of this question.

The first is simply, "What prevents someone from taking down Chattor's servers and disabling it?"
This is easy:
There *are* no servers.
There's nothing to shut down here.
The only 'weak link', so to speak, is the Tor network, which *can* be blocked.
Fortunately, Tor itself has defenses against this, and Chattor is compatible with all of them.

The seond is more complex: "What prevents someone from selectively blocking Chattor from being used?"
All traffic going over Tor is inherently encrypted and anonymized.
It's identifiable as Tor traffic, but it's impossible for anyone in the middle to tell whether it's Chattor, web browsing, or anything else going over Tor.
So there's no way to block Chattor differently from any other Tor usage.

The third is the most complex of all: "Why can't someone keep Chattor from being installed?"
Unfortunately, there's no cryptographic defense against megacorporations updating their proprietary ecosystems to ban privacy, as unlikely as that is.
If you live in an area where your right to privacy and true ownership of your device are guaranteed legally, you might have some legal recourse, and organizations like [EFF] can help.
The good news is that the Chattor spec and reference implementation are both fully open and rehostable, so as long as anyone has a copy, it can be republished.

### I already use Signal. Should I switch to Chattor?

First, read the security warning above.

The answer is probably no, in the sense that you can -- and should -- be on both.
Signal is extremely good for fast, strongly encrypted communications.
Chattor provides decentralized and much more anonymized chat and social networking, but as a rule is slower, including not really being capable of voice chat.
Both are secure ways to chat with folks, with different priorities, advantages, and disadvantages.

One advantage Chattor can have is that by default, all of your data is encrypted unless it's actively in use.
The client you use can 
Your data can still be stolen by a sophisticated enough attack -- but if your phone gets nicked and resold, you'll be fine.

### How exactly does Chattor work?

The specification is in `docs/protocol/` in the repository, or online [here][website-protocol].

You can also peruse the source code, if you can read C.
In fact, it's strongly encouraged.
The more eyes there are looking over the code, the less time bugs have before they're discovered.

### I like Chattor and want to help. How can I?

Check out the [contributing guide][website-contributing].
In brief, though, there are three ways to help:

1.  [Report bugs][bug-report] that you find.
    (Security issues are [handled differently][insecurity]).
2.  [Describe features][feature-request] you think would be good.
    Just make sure they're features of the code in this repo, and not, say, a specific client.
3.  [Fix an issue][triaged-issues] for the maintainers.
    Not all of these are code; there's always more room for documentation.

If you're exceptionally generous with your time and effort, you can donate an audit of the code.
Any significant issues should be [reported directly][insecurity], but otherwise you're more than welcome to publish your results.
The more people audit the code, the more confident everyone can be that it's good.

  [chattor-clear-site]: https://chattor.prismatic.obloquy.work/
  [chattor-onion-site]: https://chattor.prismatic.obloquy.work/ "Okay, not yet. Soon though!"
  [EFF]: https://www.eff.org/
  [website-protocol]: https://chattor.prismatic.obloquy.work/protocol
  [insecurity]: https://prismatic.obloquy.work/insecurity
  [bug-report]: https://github.com/prismatic-obloquy/chattor/issues/new?assignees=&labels=bug-report%2C+needs-triage&template=BUG-REPORT.md
  [feature-request]: https://github.com/prismatic-obloquy/chattor/issues/new?assignees=&labels=feature-request%2C+needs-triage&template=FEATURE-REQUEST.md
  [triaged-issues]: https://github.com/prismatic-obloquy/chattor/labels/triaged
  [questions]: https://github.com/prismatic-obloquy/chattor/discussions/new?category=questions
