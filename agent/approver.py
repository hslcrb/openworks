class Approver:
    """Simple approval helper. In a real application this would be
    integrated with a GUI confirmation flow or system prompt audit log.
    """

    def __init__(self, auto_approve: bool = False):
        self.auto_approve = auto_approve
        self.approved = {}

    def request(self, action: str, details: str = "") -> bool:
        """Request approval for `action`. Returns True if approved.

        This implementation reads from stdin for interactive approval.
        """
        if self.auto_approve:
            self.approved[action] = True
            return True

        print("--- ACTION REQUIRES APPROVAL ---")
        print(action)
        if details:
            print(details)
        while True:
            try:
                ans = input("Approve? (y/n) > ").strip().lower()
            except EOFError:
                # non-interactive environment: deny by default
                self.approved[action] = False
                return False
            if ans in ("y", "yes"):
                self.approved[action] = True
                return True
            if ans in ("n", "no"):
                self.approved[action] = False
                return False
            print("Please enter y or n.")
