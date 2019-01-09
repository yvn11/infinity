FROM zlynch/spark:2.4.0

ENV WOODY_ROOT /opt/woody
WORKDIR $WOODY_ROOT

COPY Makefile requirements.txt $WOODY_ROOT/
COPY woody $WOODY_ROOT/woody 
COPY config $WOODY_ROOT/config
COPY scripts $WOODY_ROOT/scripts
CMD ["scripts/aggr_cli.sh"]
