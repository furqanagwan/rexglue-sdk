# Xex2 info: system source notes

This record preserves technical and API notes moved from `include/rex/system/util/xex2_info.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L18)

```text
// XEX version word is packed MSB-first on disk. After be<> byte-swap to native
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L19)

```text
// LE the layout in `value` is: bits 28-31 major, 24-27 minor, 8-23 build, 0-7
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L20)

```text
// qfe. x86 LE compilers allocate bitfields LSB-first, so list LSB fields first
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L21)

```text
// to match the on-disk packing.
```

## Source note 5, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L43)

```text
// 8 + 1 for \0
```

## Source note 6, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L48)

```text
// kXEPESection*
```

## Source note 7, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L55)

```text
// Function address
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L81)

```text
// else 64KB
```

## Source note 9, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L165)

```text
// ESRB (Entertainment Software Rating Board)
```

## Source note 10, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L175)

```text
// PEGI (Pan European Game Information)
```

## Source note 11, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L184)

```text
// PEGI (Pan European Game Information) - Finland
```

## Source note 12, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L193)

```text
// PEGI (Pan European Game Information) - Portugal
```

## Source note 13, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L202)

```text
// BBFC (British Board of Film Classification) - UK/Ireland
```

## Source note 14, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L214)

```text
// CERO (Computer Entertainment Rating Organization)
```

## Source note 15, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L223)

```text
// USK (Unterhaltungssoftware SelbstKontrolle)
```

## Source note 16, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L232)

```text
// OFLC (Office of Film and Literature Classification) - Australia
```

## Source note 17, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L240)

```text
// OFLC (Office of Film and Literature Classification) - New Zealand
```

## Source note 18, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L248)

```text
// KMRB (Korea Media Rating Board)
```

## Source note 19, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L265)

```text
// FPB (Film and Publication Board)
```

## Source note 20, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L372)

```text
// See xe_xex2_version_t for layout rationale.
```

## Source note 21, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L393)

```text
// 0x0
```

## Source note 22, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L394)

```text
// 0x8
```

## Source note 23, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L395)

```text
// 0xA
```

## Source note 24, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L396)

```text
// 0xC
```

## Source note 25, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L397)

```text
// 0xE
```

## Source note 26, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L398)

```text
// 0xF
```

## Source note 27, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L403)

```text
// 0x0
```

## Source note 28, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L404)

```text
// 0x4
```

## Source note 29, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L413)

```text
// 0x0
```

## Source note 30, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L414)

```text
// 0x4
```

## Source note 31, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L419)

```text
// 0x0
```

## Source note 32, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L420)

```text
// 0x4
```

## Source note 33, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L421)

```text
// 0x8
```

## Source note 34, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L422)

```text
// 0xC
```

## Source note 35, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L427)

```text
// 0x0
```

## Source note 36, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L428)

```text
// 0x8
```

## Source note 37, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L429)

```text
// 0xC
```

## Source note 38, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L434)

```text
// 0x0 Resource count is (size - 4) / 16
```

## Source note 39, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L435)

```text
// 0x4
```

## Source note 40, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L447)

```text
// 0x0
```

## Source note 41, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L448)

```text
// 0x4
```

## Source note 42, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L449)

```text
// 0x8
```

## Source note 43, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L450)

```text
// 0xC
```

## Source note 44, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L451)

```text
// 0x20
```

## Source note 45, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L452)

```text
// 0x30
```

## Source note 46, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L453)

```text
// 0x34
```

## Source note 47, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L454)

```text
// 0x38
```

## Source note 48, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L455)

```text
// 0x3C
```

## Source note 49, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L456)

```text
// 0x40
```

## Source note 50, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L457)

```text
// 0x44
```

## Source note 51, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L458)

```text
// 0x48
```

## Source note 52, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L459)

```text
// 0x4C
```

## Source note 53, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L471)

```text
// 0x0
```

## Source note 54, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L472)

```text
// 0x4
```

## Source note 55, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L473)

```text
// 0x8
```

## Source note 56, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L474)

```text
// 0xC
```

## Source note 57, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L475)

```text
// 0x10
```

## Source note 58, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L476)

```text
// 0x11
```

## Source note 59, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L477)

```text
// 0x12
```

## Source note 60, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L478)

```text
// 0x13
```

## Source note 61, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L479)

```text
// 0x14
```

## Source note 62, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L492)

```text
// 0x0
```

## Source note 63, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L494)

```text
// 0x4
```

## Source note 64, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L495)

```text
// 0x8
```

## Source note 65, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L496)

```text
// 0xC string_table_size bytes
```

## Source note 66, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L501)

```text
// 0x0
```

## Source note 67, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L502)

```text
// 0x4
```

## Source note 68, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L503)

```text
// 0x18
```

## Source note 69, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L504)

```text
// 0x1C
```

## Source note 70, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L505)

```text
// 0x20
```

## Source note 71, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L506)

```text
// 0x24
```

## Source note 72, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L507)

```text
// 0x26
```

## Source note 73, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L508)

```text
// 0x28
```

## Source note 74, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L527)

```text
// 0x0
```

## Source note 75, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L530)

```text
// 0x4
```

## Source note 76, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L531)

```text
// 0x4
```

## Source note 77, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L536)

```text
// 0x0 'XEX2'
```

## Source note 78, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L537)

```text
// 0x4
```

## Source note 79, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L538)

```text
// 0x8
```

## Source note 80, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L539)

```text
// 0xC
```

## Source note 81, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L540)

```text
// 0x10
```

## Source note 82, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L541)

```text
// 0x14
```

## Source note 83, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L543)

```text
// 0x18
```

## Source note 84, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L548)

```text
// 0x0
```

## Source note 85, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L554)

```text
// 0x4
```

## Source note 86, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L558)

```text
// 0x0
```

## Source note 87, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L559)

```text
// 0x4
```

## Source note 88, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L560)

```text
// 0x8
```

## Source note 89, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L561)

```text
// 0x108 unk length
```

## Source note 90, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L562)

```text
// 0x10C
```

## Source note 91, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L563)

```text
// 0x110
```

## Source note 92, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L564)

```text
// 0x114
```

## Source note 93, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L565)

```text
// 0x128
```

## Source note 94, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L566)

```text
// 0x12C
```

## Source note 95, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L567)

```text
// 0x140
```

## Source note 96, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L568)

```text
// 0x150
```

## Source note 97, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L569)

```text
// 0x160
```

## Source note 98, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L570)

```text
// 0x164
```

## Source note 99, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L571)

```text
// 0x178
```

## Source note 100, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L572)

```text
// 0x17C
```

## Source note 101, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L573)

```text
// 0x180
```

## Source note 102, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L574)

```text
// 0x184
```

## Source note 103, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L595)

```text
// 0x0
```

## Source note 104, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L596)

```text
// 0xC
```

## Source note 105, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L597)

```text
// 0x14
```

## Source note 106, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L598)

```text
// 0x20 must be <<16 to be accurate
```

## Source note 107, line 599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L599)

```text
// 0x24
```

## Source note 108, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L600)

```text
// 0x28
```

## Source note 109, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L601)

```text
// 0x2C ordOffset[0] + (imagebaseaddr << 16) = function
```

## Source note 110, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L604)

```text
// Little endian PE export directory (from winnt.h)
```

## Source note 111, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L614)

```text
// RVA from base of image
```

## Source note 112, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L615)

```text
// RVA from base of image
```

## Source note 113, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/util/xex2_info.h#L616)

```text
// RVA from base of image
```
