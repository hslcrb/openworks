"""Connector stubs for external services (Google Drive, Slack, Gmail).

These are placeholders. Implement OAuth and API calls per-provider.
"""

from .google_drive import GoogleDriveConnector
from .slack import SlackConnector
from .gmail import GmailConnector

__all__ = ["GoogleDriveConnector", "SlackConnector", "GmailConnector"]
