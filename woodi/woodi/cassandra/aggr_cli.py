from cassandra.cluster import Cluster
from cassandra.auth import PlainTextAuthProvider
from cassandra.protocol import SyntaxException
from woodi.common.config import Config


class AggrCli:

    def __init__(self):
        self.auth_provider = PlainTextAuthProvider(username=Config.cassandra_user, password=Config.cassandra_pass)
        self.conn = Cluster(Config.cassandra_servers, Config.cassandra_port, auth_provider=self.auth_provider)
        self.sess = self.conn.connect(keyspace='aggregate')
    
    def cleanup(self):
        print('aggr shutdown')
        if self.conn != None:
            self.conn.shutdown()


if __name__ == '__main__':
    cli = AggrCli()
    try:
        while True:
            stmt = input()
            err = cli.sess.execute(stmt)
    except SyntaxException as e:
        print(e)
    except (EOFError,KeyboardInterrupt):
        cli.cleanup()
