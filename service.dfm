object reClientService: TreClientService
  OldCreateOrder = False
  DisplayName = 'reClientService'
  AfterInstall = ServiceAfterInstall
  BeforeUninstall = ServiceBeforeUninstall
  OnExecute = ServiceExecute
  Height = 150
  Width = 215
end
