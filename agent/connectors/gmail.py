class GmailConnector:
    """Placeholder Gmail connector.

    Implement OAuth and methods to send and list messages.
    """

    def __init__(self, credentials=None):
        self.credentials = credentials

    def send_message(self, to: str, subject: str, body: str):
        raise NotImplementedError("Gmail send_message not implemented.")

    def list_messages(self, query: str = None):
        raise NotImplementedError("Gmail list_messages not implemented.")
