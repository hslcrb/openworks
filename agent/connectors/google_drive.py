class GoogleDriveConnector:
    """Placeholder Google Drive connector.

    Implement authentication via OAuth2 and provide methods to list,
    download, and upload files. This file intentionally contains only
    method signatures and documentation to avoid shipping credentials.
    """

    def __init__(self, credentials=None):
        self.credentials = credentials

    def list_files(self, folder_id: str = None):
        """Return a list of file metadata in the folder.

        Raises NotImplementedError until implemented.
        """
        raise NotImplementedError("Google Drive connector not implemented.")

    def download(self, file_id: str, dest_path: str):
        raise NotImplementedError("Google Drive download not implemented.")

    def upload(self, src_path: str, folder_id: str = None):
        raise NotImplementedError("Google Drive upload not implemented.")
