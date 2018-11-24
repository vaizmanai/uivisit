object reService: TreService
  OldCreateOrder = False
  DisplayName = 'reVisit'
  AfterInstall = ServiceAfterInstall
  BeforeUninstall = ServiceBeforeUninstall
  OnExecute = ServiceExecute
  Height = 150
  Width = 215
end
