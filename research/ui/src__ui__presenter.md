# Presenter: ui source notes

This record preserves technical and API notes moved from `src/ui/presenter.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L252)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 2, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L286)

```text
// No intrusive lifetime management must be performed from UI drawers - defer
```

## Source note 3, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L287)

```text
// it if needed.
```

## Source note 4, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L301)

```text
// Null the pointer to prevent an infinite loop between SetPresenter and
```

## Source note 5, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L302)

```text
// SetWindowSurfaceFromUIThread calling each other.
```

## Source note 6, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L309)

```text
// No intrusive lifetime management must be performed from UI drawers - defer
```

## Source note 7, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L310)

```text
// it if needed.
```

## Source note 8, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L313)

```text
// There can't be a valid surface pointer without a window, as a surface is
```

## Source note 9, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L314)

```text
// created and owned by the window.
```

## Source note 10, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L318)

```text
// Nothing has changed (or a recursive SetWindowSurfaceFromUIThread >
```

## Source note 11, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L319)

```text
// SetPresenter > SetWindowSurfaceFromUIThread call).
```

## Source note 12, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L323)

```text
// Disconnect from the current surface.
```

## Source note 13, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L325)

```text
// Take ownership of painting, and also stop accepting paint requests from
```

## Source note 14, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L326)

```text
// the guest output thread - the window (which is required for making them)
```

## Source note 15, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L327)

```text
// may be going away, and there will be a forced paint when the connection
```

## Source note 16, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L328)

```text
// becomes available.
```

## Source note 17, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L337)

```text
// The window pointer may be accessed by the guest output thread if painting
```

## Source note 18, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L338)

```text
// is possible (or was possible, but the paint attempt has resulted in the
```

## Source note 19, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L339)

```text
// implementation reporting that the connection has become outdated).
```

## Source note 20, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L340)

```text
// However, a painting connection is currently not established at all, so
```

## Source note 21, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L341)

```text
// it's safe to modify the window pointer here.
```

## Source note 22, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L343)

```text
// Detach from the old window if attaching to a different one or just
```

## Source note 23, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L344)

```text
// detaching. SetPresenter for the new window might have been called without
```

## Source note 24, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L345)

```text
// it having been called with nullptr for the old window.
```

## Source note 25, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L348)

```text
// Null the pointer to prevent an infinite loop between SetPresenter and
```

## Source note 26, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L349)

```text
// SetWindowSurfaceFromUIThread calling each other.
```

## Source note 27, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L354)

```text
// Attach to the new one.
```

## Source note 28, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L355)

```text
// This function is called from SetPresenter - don't need to notify the
```

## Source note 29, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L356)

```text
// window of this, as it itself has triggered this.
```

## Source note 30, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L368)

```text
// Request to paint as soon as possible in the UI thread if connected
```

## Source note 31, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L369)

```text
// successfully.
```

## Source note 32, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L377)

```text
// No intrusive lifetime management must be performed from UI drawers - defer
```

## Source note 33, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L378)

```text
// it if needed.
```

## Source note 34, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L389)

```text
// No intrusive lifetime management must be performed from UI drawers - defer
```

## Source note 35, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L390)

```text
// it if needed.
```

## Source note 36, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L397)

```text
// Let the UI thread take ownership of painting (so the connection can be
```

## Source note 37, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L398)

```text
// updated) in a smooth way - downgrade to kUIThreadOnRequest rather than
```

## Source note 38, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L399)

```text
// kNone, because a forced repaint may not be necessary if, for example, the
```

## Source note 39, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L400)

```text
// size internally turns out to be the same after the update, and in this case
```

## Source note 40, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L401)

```text
// the current image may be kept - but the new one must not be missed either
```

## Source note 41, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L402)

```text
// if it becomes available during the resize.
```

## Source note 42, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L410)

```text
// Request to repaint as soon as possible in the UI thread if needed.
```

## Source note 43, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L417)

```text
// If there is no surface, this will be a no-op, nothing outdated, nothing to
```

## Source note 44, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L418)

```text
// paint. However, an explicit monitor check is needed because UI framerate
```

## Source note 45, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L419)

```text
// limiting may be tied to signals from the OS for the monitor - but painting
```

## Source note 46, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L420)

```text
// may still occur, for instance, if drawing to a composition surface in the
```

## Source note 47, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L421)

```text
// OS (which will still be live even if the window goes outside any monitor).
```

## Source note 48, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L422)

```text
// But a surface check still won't cause harm, for simplicity.
```

## Source note 49, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L427)

```text
// Defer changes to the paint mode as well as window paint requests, and do
```

## Source note 50, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L428)

```text
// them in this function so they're consistent with the assumptions made here.
```

## Source note 51, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L434)

```text
// Actualize the connection if the UI needs to be drawn if there was some
```

## Source note 52, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L435)

```text
// explicit paint request (the guest output has been refreshed, and the guest
```

## Source note 53, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L436)

```text
// output thread was asked not to present directly due as the UI needs to be
```

## Source note 54, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L437)

```text
// drawn, or some surface state change has happened so the guest output needs
```

## Source note 55, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L438)

```text
// to be displayed as soon as possible without waiting for the guest to
```

## Source note 56, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L439)

```text
// refresh it, or the guest output thread has been notified that the
```

## Source note 57, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L440)

```text
// connection has become outdated and has requested the UI thread to
```

## Source note 58, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L441)

```text
// reconnect).
```

## Source note 59, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L444)

```text
// Reset ui_thread_paint_requested_ unconditionally also, regardless of
```

## Source note 60, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L445)

```text
// whether the UI needs to be drawn - the flag may be set to try reconnecting,
```

## Source note 61, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L446)

```text
// for example.
```

## Source note 62, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L454)

```text
// Take ownership of painting if it's currently owned by the guest output
```

## Source note 63, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L455)

```text
// thread (downgrade from kGuestOutputThreadImmediately to
```

## Source note 64, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L456)

```text
// kUIThreadOnRequest - not to kNone so if during this paint a new guest
```

## Source note 65, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L457)

```text
// output frame is generated, the notification will still be sent to the UI
```

## Source note 66, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L458)

```text
// thread rather than dropped, so the frame won't be skipped). This is
```

## Source note 67, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L459)

```text
// needed to be able not only to paint, but also to try to recover from an
```

## Source note 68, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L460)

```text
// outdated surface.
```

## Source note 69, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L464)

```text
// Try to recover from the connection becoming outdated in the previous
```

## Source note 70, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L465)

```text
// paint.
```

## Source note 71, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L469)

```text
// If still paintable or recovered successfully, paint.
```

## Source note 72, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L471)

```text
// The paint mode might have been set to kNone when the connection was
```

## Source note 73, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L472)

```text
// marked as outdated last time. Or, if wasn't reconnecting, there was
```

## Source note 74, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L473)

```text
// some other incorrect situation that caused the paint mode to be set to
```

## Source note 75, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L474)

```text
// kNone for an active connection. Make sure that the current paint mode
```

## Source note 76, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L475)

```text
// is consistent with painting from the UI thread.
```

## Source note 77, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L478)

```text
// Limit the frame rate of the UI, usually to the monitor refresh rate,
```

## Source note 78, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L479)

```text
// in a way so that the UI won't be stealing all the remaining GPU
```

## Source note 79, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L480)

```text
// resources if it's repainted continuously, and the window system itself
```

## Source note 80, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L481)

```text
// doesn't limit the frame rate.
```

## Source note 81, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L486)

```text
// Request another PaintFromUIThread which will try to recover from the
```

## Source note 82, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L487)

```text
// outdated connection in the next frame (not immediately, so the
```

## Source note 83, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L488)

```text
// windowing system has some time to prepare what may be required to
```

## Source note 84, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L489)

```text
// recover from it, such as to send a resize event).
```

## Source note 85, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L493)

```text
// If can't paint anymore, notify the paint mode refresh below (which is not
```

## Source note 86, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L494)

```text
// guaranteed to have access to have ownership of painting as it's taken
```

## Source note 87, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L495)

```text
// here only conditionally, thus can't know whether the connection is
```

## Source note 88, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L496)

```text
// actually in a paintable state).
```

## Source note 89, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L502)

```text
// Transfer the ownership of painting back to the guest output thread if it
```

## Source note 90, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L503)

```text
// was taken or if needed for any reason (however, it's taken conditionally -
```

## Source note 91, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L504)

```text
// no guarantees that the actual connection state is accessible here, so only
```

## Source note 92, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L505)

```text
// checking whether the mode is not kNone currently, not the connection
```

## Source note 93, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L506)

```text
// state), and overall synchronize the state taking into account both what has
```

## Source note 94, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L507)

```text
// been done in this function and what could have been done by the UI drawer
```

## Source note 95, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L508)

```text
// callbacks.
```

## Source note 96, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L514)

```text
// Check if the device has been lost. There's no point in requesting repaint
```

## Source note 97, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L515)

```text
// if it has happened anyway, it won't be possible to satisfy such request
```

## Source note 98, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L516)

```text
// with the current Presenter.
```

## Source note 99, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L522)

```text
// The loss callback might have destroyed the presenter, must not do
```

## Source note 100, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L523)

```text
// anything with `this` anymore.
```

## Source note 101, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L527)

```text
// Request refresh if needed.
```

## Source note 102, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L528)

```text
// Can't check the exact paintability as the connection state may currently
```

## Source note 103, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L529)

```text
// be owned by the guest output thread, so check conservatively via
```

## Source note 104, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L530)

```text
// paint_mode_.
```

## Source note 105, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L532)

```text
// Immediately paint the guest output if requested explicitly or if the UI
```

## Source note 106, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L533)

```text
// has hidden itself.
```

## Source note 107, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L562)

```text
// If failed to refresh, don't send the currently writable image to the
```

## Source note 108, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L563)

```text
// mailbox as it may be in an undefined state. Don't disable the guest
```

## Source note 109, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L564)

```text
// output either though because the failure may be something transient.
```

## Source note 110, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L569)

```text
// Request presenting a blank image if there was a true image previously,
```

## Source note 111, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L570)

```text
// but not now.
```

## Source note 112, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L577)

```text
// Make the new image the next to present on the host (the "ready" one),
```

## Source note 113, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L578)

```text
// replacing the one already specified as the next (dropping it instead of
```

## Source note 114, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L579)

```text
// enqueueing the new image after it) to achieve the lowest latency (also,
```

## Source note 115, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L580)

```text
// after switching from UI thread painting to doing it in the guest output
```

## Source note 116, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L581)

```text
// thread, will immediately recover to having the latest frame always sent to
```

## Source note 117, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L582)

```text
// the host present call on the CPU and all frames reaching a present call).
```

## Source note 118, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L585)

```text
// Desired acquired = current acquired (changed only by the consumers).
```

## Source note 119, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L586)

```text
// Desired ready = current writable.
```

## Source note 120, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L587)

```text
// memory_order_acq_rel to acquire the new writable image and to release the
```

## Source note 121, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L588)

```text
// current one (to let the consumers take it, from ready to acquired).
```

## Source note 122, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L593)

```text
// Now, it's known that `ready == writable` on the host presentation side.
```

## Source note 123, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L594)

```text
// Take the next `writable` with this assumption about its current value in
```

## Source note 124, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L595)

```text
// mind.
```

## Source note 125, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L598)

```text
// The new image has already been acquired by the time the compare-exchange
```

## Source note 126, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L599)

```text
// loop has finished (acquired == ready == currently writable).
```

## Source note 127, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L600)

```text
// It's a valid situation from the ownership perspective, and the semantics
```

## Source note 128, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L601)

```text
// of the weak compare-exchange explicitly permit spurious `false` results.
```

## Source note 129, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L602)

```text
// (3 - a - b) % 3 cannot be used here, as (3 - a - a) % 3 results in `a` -
```

## Source note 130, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L603)

```text
// the same index.
```

## Source note 131, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L604)

```text
// Take any free image. Preferably using + 1, not ^ 1, so if the guest needs
```

## Source note 132, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L605)

```text
// to await any GPU work referencing the image, it will wait for the frame 3
```

## Source note 133, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L606)

```text
// frames ago, not 2, if this happens repeatedly.
```

## Source note 134, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L609)

```text
// Take the image other than the last acquired one and the new one,
```

## Source note 135, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L610)

```text
// currently not accessible to the host presentation.
```

## Source note 136, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L614)

```text
// Trigger the presentation on the host.
```

## Source note 137, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L620)

```text
// Neither painting nor window paint requesting is accessible.
```

## Source note 138, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L623)

```text
// Only window paint requesting is accessible.
```

## Source note 139, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L627)

```text
// Both painting and window paint requesting are accessible.
```

## Source note 140, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L637)

```text
// Handle GPU loss when not in the middle of the function anymore, and
```

## Source note 141, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L638)

```text
// lifecycle management from the GPU loss callback is fine on the UI thread.
```

## Source note 142, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L651)

```text
// For simplicity, this may be called externally repeatedly.
```

## Source note 143, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L652)

```text
// Lock the mutex only when something has been modified, and also don't
```

## Source note 144, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L653)

```text
// request UI thread guest output redraws when not needed.
```

## Source note 145, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L699)

```text
// Coarsely check the availability of painting and of the window (for
```

## Source note 146, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L700)

```text
// calling RequestPaint) via paint_mode_ because the actual painting
```

## Source note 147, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L701)

```text
// connection state may currently be owned not by the UI thread.
```

## Source note 148, line 704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L704)

```text
// Defer until the end of the current paint if called from, for
```

## Source note 149, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L705)

```text
// instance, a UI drawer.
```

## Source note 150, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L716)

```text
// Obtain whether the iterator list was empty before erasing in case of
```

## Source note 151, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L717)

```text
// replacing with a new entry with a different Z order happens.
```

## Source note 152, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L720)

```text
// Check if already added.
```

## Source note 153, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L728)

```text
// Keep the same last draw index to prevent the drawer from being executed
```

## Source note 154, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L729)

```text
// twice if increasing its Z order during the drawer loop.
```

## Source note 155, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L731)

```text
// If removing the drawer that is the next in the current drawer loop, skip
```

## Source note 156, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L732)

```text
// it (in a multimap, only one element iterator is invalidated).
```

## Source note 157, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L740)

```text
// If adding to the Z layer currently being processed (for drawing, from the
```

## Source note 158, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L741)

```text
// lowest to the highest), or to layers in between the current and the
```

## Source note 159, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L742)

```text
// previously next, make sure the new drawer is executed too.
```

## Source note 160, line 756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L756)

```text
// If removing the drawer that is the next in the current drawer loop, skip
```

## Source note 161, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L757)

```text
// it (in a multimap, only one element iterator is invalidated).
```

## Source note 162, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L769)

```text
// The paint request will be done once in the end of PaintFromUIThread
```

## Source note 163, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L770)

```text
// according to the actual state at the moment that happens. It's common for
```

## Source note 164, line 771

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L771)

```text
// drawers to call this (even every frame), and no need to do too many OS
```

## Source note 165, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L772)

```text
// paint request calls.
```

## Source note 166, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L776)

```text
// The connection state may be owned by the guest output thread now rather
```

## Source note 167, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L777)

```text
// than the UI thread, check whether it's not pointless to make the request
```

## Source note 168, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L778)

```text
// coarsely via paint_mode_.
```

## Source note 169, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L780)

```text
// The window must be present, otherwise the conditions wouldn't have been
```

## Source note 170, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L781)

```text
// met.
```

## Source note 171, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L792)

```text
// Initialize UI frame rate limiting.
```

## Source note 172, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L802)

```text
// Get the up-to-date guest output paint configuration settings set by the
```

## Source note 173, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L803)

```text
// UI thread.
```

## Source note 174, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L808)

```text
// Lock the mutex to make sure the image that will be acquired now is owned
```

## Source note 175, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L809)

```text
// exclusively by the calling thread for the time while this mutex is still
```

## Source note 176, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L810)

```text
// locked (it needs to be held by the consumer while working with anything
```

## Source note 177, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L811)

```text
// that depends on the image now being acquired or its index in the mailbox).
```

## Source note 178, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L813)

```text
// Acquire the up-to-date ready guest image (may be new, in this case the last
```

## Source note 179, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L814)

```text
// acquired one will be released, or still the same or no refresh has happened
```

## Source note 180, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L815)

```text
// since the last consumption).
```

## Source note 181, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L816)

```text
// memory_order_relaxed here because the ready index from this load will be
```

## Source note 182, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L817)

```text
// used directly only if it's the same as during the last consumption - thus
```

## Source note 183, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L818)

```text
// the image has already been acquired previously, no need for
```

## Source note 184, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L819)

```text
// memory_order_acquire (if the image has been acquired by a different
```

## Source note 185, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L820)

```text
// consumer though, the consumer mutex performs memory access ordering).
```

## Source note 186, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L823)

```text
// Desired acquired = current ready.
```

## Source note 187, line 824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L824)

```text
// Desired ready = current ready (changed only by the producer).
```

## Source note 188, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L827)

```text
// Either the same image as during the last consumption, or a new one, is
```

## Source note 189, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L828)

```text
// satisfying. However, if it's new, using memory_order_acq_rel to acquire the
```

## Source note 190, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L829)

```text
// new ready image (to make it acquired) and to release the old acquired image
```

## Source note 191, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L830)

```text
// (to let the producer take it as writable).
```

## Source note 192, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L839)

```text
// Give the current acquired image to the caller, or UINT32_MAX if it's
```

## Source note 193, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L840)

```text
// inactive.
```

## Source note 194, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L857)

```text
// Initialize one clear rectangle for the case of drawing no guest output, for
```

## Source note 195, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L858)

```text
// consistency with fewer state dependencies.
```

## Source note 196, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L863)

```text
// For safety such as division by zero prevention.
```

## Source note 197, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L871)

```text
// Multiplication-division rounding to the nearest.
```

## Source note 198, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L876)

```text
// Plus old_scale / 2 for positive values, minus old_scale / 2 for
```

## Source note 199, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L877)

```text
// negative values for consistent rounding for both positive and
```

## Source note 200, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L878)

```text
// negative values (as the `/` operator rounds towards zero).
```

## Source note 201, line 880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L880)

```text
// (-3 - 1) / 3 == -1
```

## Source note 202, line 881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L881)

```text
// (-2 - 1) / 3 == -1
```

## Source note 203, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L882)

```text
// (-1 - 1) / 3 == 0
```

## Source note 204, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L884)

```text
// (0 + 1) / 3 == 0
```

## Source note 205, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L885)

```text
// (1 + 1) / 3 == 0
```

## Source note 206, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L886)

```text
// (2 + 1) / 3 == 1
```

## Source note 207, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L891)

```text
// Final output location and dimensions.
```

## Source note 208, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L892)

```text
// All host location calculations are DPI-independent, conceptually depending
```

## Source note 209, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L893)

```text
// only on the aspect ratios, not the absolute values.
```

## Source note 210, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L897)

```text
// The window is wider that the source - crop along Y to preserve the aspect
```

## Source note 211, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L898)

```text
// ratio while stretching throughout the entire surface's width, then limit
```

## Source note 212, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L899)

```text
// the Y cropping via letterboxing or stretching along X.
```

## Source note 213, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L907)

```text
// Scale the desired width by the H:W aspect ratio (inverse of W:H) to get
```

## Source note 214, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L908)

```text
// the height.
```

## Source note 215, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L914)

```text
// Don't crop out more than the safe area margin - letterbox or stretch.
```

## Source note 216, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L922)

```text
// output_width might have been rounded up already by rescale_unsigned, so
```

## Source note 217, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L923)

```text
// rounding down in this division.
```

## Source note 218, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L929)

```text
// output_height might have been rounded up already by rescale_unsigned, so
```

## Source note 219, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L930)

```text
// rounding down in this division.
```

## Source note 220, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L933)

```text
// The window is taller that the source - crop along X to preserve the
```

## Source note 221, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L934)

```text
// aspect ratio while stretching throughout the entire surface's height,
```

## Source note 222, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L935)

```text
// then limit the X cropping via letterboxing or stretching along Y.
```

## Source note 223, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L943)

```text
// Scale the desired height by the W:H aspect ratio to get the width.
```

## Source note 224, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L949)

```text
// Don't crop out more than the safe area margin - letterbox or stretch.
```

## Source note 225, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L957)

```text
// output_height might have been rounded up already by rescale_unsigned,
```

## Source note 226, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L958)

```text
// so rounding down in this division.
```

## Source note 227, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L964)

```text
// output_width might have been rounded up already by rescale_unsigned, so
```

## Source note 228, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L965)

```text
// rounding down in this division.
```

## Source note 229, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L969)

```text
// Convert the location from surface pixels (which have 1:1 aspect ratio
```

## Source note 230, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L970)

```text
// relatively to the physical display) to render target pixels (the render
```

## Source note 231, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L971)

```text
// target size may be arbitrary with any aspect ratio, but if it's different
```

## Source note 232, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L972)

```text
// than the surface size, the OS is expected to stretch it to the surface
```

## Source note 233, line 973

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L973)

```text
// boundaries), preserving the aspect ratio.
```

## Source note 234, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L987)

```text
// The out-of-bounds checks are needed for correct letterbox calculations.
```

## Source note 235, line 988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L988)

```text
// Though this normally shouldn't happen, but in case of rounding issues with
```

## Source note 236, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L989)

```text
// extreme values.
```

## Source note 237, line 992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L992)

```text
// In rare cases (for example, when surface and render-target coordinate
```

## Source note 238, line 993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L993)

```text
// spaces diverge unexpectedly), the computed output may become anchored at
```

## Source note 239, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L994)

```text
// the top-left and smaller than the host render target. This results in only
```

## Source note 240, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L995)

```text
// a top-left region being presented with black right/bottom areas.
```

## Source note 241, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1015)

```text
// The output image may have a part of it outside the final render target (if
```

## Source note 242, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1016)

```text
// using the overscan area to stretch the image to the entire surface while
```

## Source note 243, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1017)

```text
// preserving the guest aspect ratio if it differs from the host one, for
```

## Source note 244, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1018)

```text
// instance). While the final render target size is known to be within the
```

## Source note 245, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1019)

```text
// host render target / image size limit, the intermediate images may be
```

## Source note 246, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1020)

```text
// larger than that as they include the overscan area that will be outside the
```

## Source note 247, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1021)

```text
// screen. Make sure the intermediate images can't be larger than the maximum
```

## Source note 248, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1022)

```text
// render target size.
```

## Source note 249, line 1031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1031)

```text
// FidelityFX Super Resolution and Contrast Adaptive Sharpening only work
```

## Source note 250, line 1032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1032)

```text
// good for up to 2x2 upscaling due to the way they fetch texels.
```

## Source note 251, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1033)

```text
// CAS is primarily a sharpening filter, not an upscaling one (its upscaling
```

## Source note 252, line 1034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1034)

```text
// eliminates reduces blurriness, but doesn't preserve the shapes of edges,
```

## Source note 253, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1035)

```text
// and executing it multiple times will only result in oversharpening. So,
```

## Source note 254, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1036)

```text
// using it for scales only of up to 2x2, then simply stretching with
```

## Source note 255, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1037)

```text
// bilinear filtering.
```

## Source note 256, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1038)

```text
// EASU of FSR, however, preserves edges, it's not supposed to blur them or
```

## Source note 257, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1039)

```text
// to make them jagged, so it can be executed multiple times - running
```

## Source note 258, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1040)

```text
// multiple EASU passes for scale factors of over 2x2.
```

## Source note 259, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1041)

```text
// Just one EASU pass rather than multiple for scaling to factors bigger
```

## Source note 260, line 1042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1042)

```text
// than 2x2 (especially significantly bigger, such as 1152x640 to 3840x2160,
```

## Source note 261, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1043)

```text
// or 3.333x3.375) results in blurry edges and an overall noisy look,
```

## Source note 262, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1044)

```text
// multiple passes improve visual stability.
```

## Source note 263, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1061)

```text
// AMD FidelityFX Super Resolution - upsample along at least one axis.
```

## Source note 264, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1062)

```text
// Using the output size clamped to the maximum render target size here as
```

## Source note 265, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1063)

```text
// EASU will always write to intermediate images, and RCAS supports only
```

## Source note 266, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1064)

```text
// 1:1.
```

## Source note 267, line 1086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1086)

```text
// Pre-temporal quality mode may request a lower render
```

## Source note 268, line 1087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1087)

```text
// resolution. Use CAS resample since bilinear is not allowed in
```

## Source note 269, line 1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1088)

```text
// intermediate passes.
```

## Source note 270, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1099)

```text
// A single temporal upscaler dispatch can target the final clamped
```

## Source note 271, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1100)

```text
// size directly, unlike the spatial multi-pass chain.
```

## Source note 272, line 1125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1125)

```text
// AMD FidelityFX Contrast Adaptive Sharpening - sharpen or downsample, or
```

## Source note 273, line 1126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1126)

```text
// upsample up to 2x2 if CAS is specified to be used for upscaling too.
```

## Source note 274, line 1127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1127)

```text
// Using the unclamped output size as CAS may be the last pass - if a
```

## Source note 275, line 1128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1128)

```text
// bilinear pass is needed afterwards, and the CAS pass will be writing to
```

## Source note 276, line 1129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1129)

```text
// an intermediate image, the CAS pass output size will be clamped while
```

## Source note 277, line 1130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1130)

```text
// adding the bilinear stretch.
```

## Source note 278, line 1141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1141)

```text
// defined(REX_HAS_FIDELITYFX_SDK)
```

## Source note 279, line 1147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1147)

```text
// If not using FidelityFX, or it has reached its upscaling capabilities,
```

## Source note 280, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1148)

```text
// but more is needed, stretch via bilinear filtering.
```

## Source note 281, line 1149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1149)

```text
// Clamp the output size of the last effect to the maximum render target
```

## Source note 282, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1150)

```text
// size because it will go to an intermediate image now.
```

## Source note 283, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1153)

```text
// RCAS only works for 1:1, clamping must be done explicitly for FSR.
```

## Source note 284, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1171)

```text
// Dithering must be applied only to the final effect since resampling and
```

## Source note 285, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1172)

```text
// sharpening filters may considering the dithering noise features and
```

## Source note 286, line 1173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1173)

```text
// amplify it.
```

## Source note 287, line 1177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1177)

```text
// Dithering has no effect for 1:1 copying of a 8bpc image.
```

## Source note 288, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1207)

```text
// Calculate the letterbox geometry.
```

## Source note 289, line 1211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1211)

```text
// Top.
```

## Source note 290, line 1223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1223)

```text
// Middle-left.
```

## Source note 291, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1233)

```text
// Middle-right.
```

## Source note 292, line 1243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1243)

```text
// Bottom.
```

## Source note 293, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1259)

```text
// May be called by the implementations only when requested.
```

## Source note 294, line 1261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1261)

```text
// Drawers can add or remove drawers (including themselves), need to ensure
```

## Source note 295, line 1262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1262)

```text
// iterator validity in this case.
```

## Source note 296, line 1267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1267)

```text
// The current iterator may be invalidated, and ui_draw_next_iterator_ may
```

## Source note 297, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1268)

```text
// be changed, during the execution of the drawer if the list of the drawers
```

## Source note 298, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1269)

```text
// is modified by it - don't assume that after the call
```

## Source note 299, line 1270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1270)

```text
// ui_draw_next_iterator_ will be the same as
```

## Source note 300, line 1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1271)

```text
// std::next(ui_draw_next_iterator_) before it.
```

## Source note 301, line 1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1273)

```text
// Don't draw twice if already drawn in this frame (may happen if the Z
```

## Source note 302, line 1274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1274)

```text
// order of a drawer was increased from below the current one to above it by
```

## Source note 303, line 1275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1275)

```text
// one of the drawers).
```

## Source note 304, line 1287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1287)

```text
// Can be modified only from the UI thread, so can skip locking if it's the
```

## Source note 305, line 1288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1288)

```text
// same.
```

## Source note 306, line 1301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1301)

```text
// The only case when kNone can be returned, for surface connection updates
```

## Source note 307, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1302)

```text
// when it's known that the UI thread currently has access to the connection
```

## Source note 308, line 1303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1303)

```text
// lifecycle.
```

## Source note 309, line 1310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1310)

```text
// Don't be causing host vertical sync CPU waits in the thread generating
```

## Source note 310, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1311)

```text
// the guest output.
```

## Source note 311, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1315)

```text
// The UI can be drawn only by the UI thread, and it needs to be drawn -
```

## Source note 312, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1316)

```text
// paint in the UI thread.
```

## Source note 313, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1319)

```text
// Only the guest output needs to be drawn - let the guest output thread
```

## Source note 314, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1320)

```text
// present immediately for a lower latency.
```

## Source note 315, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1339)

```text
// Validate that painting lifecycle is accessible by the UI thread currently,
```

## Source note 316, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1340)

```text
// not given to the guest output thread. The mode can be modified only by
```

## Source note 317, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1341)

```text
// the UI thread, so no need to lock the mutex.
```

## Source note 318, line 1344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1344)

```text
// Initialize repaint_needed_out for failure cases.
```

## Source note 319, line 1349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1349)

```text
// If the connection state is kUnconnectedSurfaceReportedUnusable, the
```

## Source note 320, line 1350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1350)

```text
// implementation has reported that the surface is not usable by the presenter
```

## Source note 321, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1351)

```text
// at all, and it's pointless to retry connecting to it.
```

## Source note 322, line 1357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1357)

```text
// The surface is currently zero-area (or has become zero-area), try again
```

## Source note 323, line 1358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1358)

```text
// when it's resized.
```

## Source note 324, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1373)

```text
// Fallthrough to common success handling.
```

## Source note 325, line 1375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1375)

```text
// Don't know yet what the first result was (success or suboptimal).
```

## Source note 326, line 1404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1404)

```text
// Can be called from any thread if an existing window_ is available in it,
```

## Source note 327, line 1405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1405)

```text
// and it's known to have a Surface that will be the same throughout this
```

## Source note 328, line 1406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1406)

```text
// call - not doing any checks whether this request can be satisfied
```

## Source note 329, line 1407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1407)

```text
// theoretically. For safety, check whether the window exists unconditionally.
```

## Source note 330, line 1411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1411)

```text
// Invalidation pending already, no need to do it twice.
```

## Source note 331, line 1422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1422)

```text
// For dropping the monitor when the window is closing and is losing its
```

## Source note 332, line 1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1423)

```text
// surface, the existence of `surface_` (which implies that `window_` exists
```

## Source note 333, line 1424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1424)

```text
// too) must be the condition for a non-null monitor, not just the existence
```

## Source note 334, line 1425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1425)

```text
// of `window_`.
```

## Source note 335, line 1429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1429)

```text
// The HWND may be non-existent if the window has been closed and destroyed
```

## Source note 336, line 1430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1430)

```text
// (the HWND, not the rex::ui::Window) already.
```

## Source note 337, line 1438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1438)

```text
// If a monitor has been newly connected, it won't appear in the old
```

## Source note 338, line 1439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1439)

```text
// factory, need to recreate it.
```

## Source note 339, line 1459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1459)

```text
// If the adapter was recreated, and the old output was released before its
```

## Source note 340, line 1460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1460)

```text
// destruction, notifying is still required - the vertical blank wait thread
```

## Source note 341, line 1461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1461)

```text
// might have entered the condition variable wait already as the output was
```

## Source note 342, line 1462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1462)

```text
// null.
```

## Source note 343, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1493)

```text
// Make outdated if previously optimal, now suboptimal, but don't cause
```

## Source note 344, line 1494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1494)

```text
// the connection to become outdated if it has been suboptimal from the
```

## Source note 345, line 1495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1495)

```text
// very beginning.
```

## Source note 346, line 1504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1504)

```text
// Another issue not directly related to the surface connection.
```

## Source note 347, line 1512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1512)

```text
// Defer the refresh so no dangerous lifecycle-related changes happen during
```

## Source note 348, line 1513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1513)

```text
// drawing.
```

## Source note 349, line 1521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1521)

```text
// Not connected, no point in refreshing (checking a more conservative
```

## Source note 350, line 1522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1522)

```text
// paint_mode_ because the actual connection state may currently be owned by
```

## Source note 351, line 1523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1523)

```text
// the guest output thread instead) or in toggling the ownership (the rest
```

## Source note 352, line 1524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1524)

```text
// of the function can assume it's not kNone).
```

## Source note 353, line 1529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1529)

```text
// Require the UI thread to paint if it needs the UI, or let the guest
```

## Source note 354, line 1530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1530)

```text
// output thread paint immediately if not.
```

## Source note 355, line 1532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1532)

```text
// Make sure the ticks for limiting the UI frame rate are sent.
```

## Source note 356, line 1536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1536)

```text
// Request painting so the changes to the UI drawer list are reflected as
```

## Source note 357, line 1537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1537)

```text
// quickly as possible.
```

## Source note 358, line 1538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1538)

```text
// RequestUIPaintFromUIThread is not enough, because a paint request is also
```

## Source note 359, line 1539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1539)

```text
// needed if disabling the UI, to force paint a frame without the UI as soon
```

## Source note 360, line 1540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1540)

```text
// as possible - it can't be dropped if ui_drawers_ is empty.
```

## Source note 361, line 1541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1541)

```text
// The coarse painting availability (and thus the availability of `window_`,
```

## Source note 362, line 1542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1542)

```text
// which is required for the paint mode to be anything else than kNone) has
```

## Source note 363, line 1543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1543)

```text
// already been checked above.
```

## Source note 364, line 1571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1571)

```text
// Guest output present requests should interrupt the wait as quickly as
```

## Source note 365, line 1572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1572)

```text
// possible as they should be fulfilled as early as possible.
```

## Source note 366, line 1581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1581)

```text
// If there have been multiple vblanks during the wait for some reason,
```

## Source note 367, line 1582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1582)

```text
// next time draw the UI immediately.
```

## Source note 368, line 1624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1624)

```text
// Wait for vertical blank, with the mutex unlocked (holding a new reference
```

## Source note 369, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1625)

```text
// to the current output while it's happening) so subscribers can still do
```

## Source note 370, line 1626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1626)

```text
// early-out checks.
```

## Source note 371, line 1637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1637)

```text
// Lost the ability to wait for a vertical blank on this output, notify
```

## Source note 372, line 1638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/presenter.cpp#L1638)

```text
// the waiting threads, and wait for a new one.
```
