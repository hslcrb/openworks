class SlackConnector:
    """Placeholder Slack connector.

    Implement token-based API calls to post messages, upload files, and
    read channel history.
    """

    def __init__(self, token: str = None):
        self.token = token

    def post_message(self, channel: str, text: str):
        raise NotImplementedError("Slack post_message not implemented.")

    def upload_file(self, channel: str, path: str, title: str = None):
        raise NotImplementedError("Slack upload_file not implemented.")
