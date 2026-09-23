# Contributing

For this fork, read [AGENTS.md](AGENTS.md), the
[modernization roadmap](docs/roadmap.md), and your assigned issue first.
Implementation and issues belong in `furqanagwan/rexglue-sdk`; upstream projects
are read-only references for this work. The Windows/GDK/D3D12 destination and
regression gates in the [ADRs](docs/adr/README.md) take precedence over inherited
cross-platform guidance. Preserve author/license provenance for selective ports.

Run the relevant unit/PPC, synthetic and title/vendor tests in the issue, record
actual results and blocked cases, and update the documentation with behavior
changes. Do not close a compatibility migration based only on a successful build.

See the [Contributing Guide](https://github.com/rexglue/rexglue-sdk/wiki/Development/Contributing) in the wiki for:

- Build prerequisites and setup
- Code style conventions
- Formatting and linting instructions
- Git setup (line endings, rebasing)
- PR submission workflow
