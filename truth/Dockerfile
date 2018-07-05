FROM docker.io/rust:latest

ENV TW_ROOT /opt/truth
ADD iface $TW_ROOT/iface 
ADD apps $TW_ROOT/apps 
ADD Cargo.toml $TW_ROOT/Cargo.toml

WORKDIR $TW_ROOT
RUN cargo build

ENTRYPOINT /bin/bash
