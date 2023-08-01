import asyncio
import json


class CommandServerProtocol(asyncio.Protocol):
    def __init__(self):
        self.transport = None

    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data):
        message = data.decode()
        print('Data received: {!r}/n'.format(message))

        try:
            message_dict = json.loads(message)

            print('Logs: ')
            for log in message_dict['logs']:
                print(json.dumps(log, indent=2))

            print('Monitoring Report: ')
            print(json.dumps(message_dict['monitoring_report'], indent=2))

            # # Send data back
            # commands = {
            #     "commands":[
            #         {
            #           "type": "move_forward",
            #           "count": 1,
            #           "speed": 50
            #         },
            #         {
            #           "type": "move_backward",
            #           "count": 1,
            #           "speed": 50
            #         }
            #       ]
            # }
            # self.transport.write(json.dumps(commands).encode())
        except Exception as e:
            print(e)

async def main():
    loop = asyncio.get_running_loop()

    server = await loop.create_server(
        lambda: CommandServerProtocol(),
        '0.0.0.0', 8070)

    async with server:
        await server.serve_forever()

asyncio.run(main())
